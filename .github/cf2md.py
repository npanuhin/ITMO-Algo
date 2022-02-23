from markdownify import markdownify
from bs4 import BeautifulSoup
from requests import Session
import itertools
import os
import re


MARKDOWN_TEMPLATE = "template.md"


def regex_replace(pattern, replace, text, flags=re.DOTALL | re.UNICODE):
    old_text = ""
    while old_text != text:
        old_text, text = text, re.sub(
            pattern,
            replace,
            text,
            flags=flags
        )

    return text


def md_latex(text):
    text = regex_replace(
        r"\${6}(.+?)\${6}",
        r'<p latex="\1"><pre></pre></p>',
        text
    )

    text = regex_replace(
        r"\${3}(.+?)\${3}",
        r'<span latex="\1"></span>',
        text
    )

    text = regex_replace(
        r"(<(span|p) latex=\"[^\"]*?)\\\_(.*?<\/\2>)",
        r"\1_\3",
        text
    )

    text = regex_replace(
        r"(<(span|p) latex=\"[^\"]*?\d+\\)\,(\d+.*?<\/\2>)",
        r"\1 \3",
        text
    )

    text = regex_replace(
        r"(<(span|p) latex=\"[^\"]*?)\\dots(.*?<\/\2>)",
        r"\1…\3",
        text
    )

    text = regex_replace(
        r"(<(span|p) latex=\"[^\"]*?)(\\[gl]e)([^q].*?<\/\2>)",
        r"\1\3qslant\4",
        text
    )

    return text


def pretty(string, strip=True):
    string = str(string).replace('\xa0', ' ').replace(' ', ' ').replace('≤', '⩽')
    string = re.sub(r"[ \t]+\n", '\n', string, flags=re.IGNORECASE | re.UNICODE)
    if strip:
        string = string.strip()
    return string


def soup_text(soup):
    return pretty("".join(soup.findAll(text=True, recursive=False)))


def problem2md(soup):
    problem = {}

    # Header
    header = soup.find("div", class_="header")
    if header is not None:
        title = header.find("div", class_="title")
        if title is not None:
            problem["title"] = soup_text(title)

        time_limit = header.find("div", class_="time-limit")
        # time_limit_title = time_limit.find("div", class_="property-title")
        if time_limit is not None:
            # problem["time_limit"] = "{}: {}".format(soup_text(time_limit_title), soup_text(time_limit))
            problem["time_limit"] = soup_text(time_limit)

        memory_limit = header.find("div", class_="memory-limit")
        # memory_limit_title = memory_limit.find("div", class_="property-title")
        if memory_limit is not None:
            # problem["memory_limit"] = "{}: {}".format(soup_text(memory_limit_title), soup_text(memory_limit))
            problem["memory_limit"] = soup_text(memory_limit)

        input_file = header.find("div", class_="input-file")
        # input_file_title = input_file.find("div", class_="property-title")
        if input_file is not None:
            # problem["input_file"] = "{}: {}".format(soup_text(input_file_title), soup_text(input_file))
            problem["input_file"] = soup_text(input_file)

        output_file = header.find("div", class_="output-file")
        # output_file_title = output_file.find("div", class_="property-title")
        if output_file is not None:
            # problem["output_file"] = "{}: {}".format(soup_text(output_file_title), soup_text(output_file))
            problem["output_file"] = soup_text(output_file)

    statement = soup.findChildren("div", recursive=False)[1]
    problem["statement"] = pretty(md_latex(pretty(markdownify(pretty(statement)))))

    # Input
    input_specification = soup.find("div", class_="input-specification")
    for block in input_specification.findChildren("div", recursive=False):
        block.extract()
    problem["input_specification"] = pretty(md_latex(pretty(markdownify(pretty(input_specification)))))

    # Output
    output_specification = soup.find("div", class_="output-specification")
    for block in output_specification.findChildren("div", recursive=False):
        block.extract()
    problem["output_specification"] = pretty(md_latex(pretty(markdownify(pretty(output_specification)))))

    # Tests
    tests = []
    cur_test = {"input": None, "output": None}
    for test_block in soup.find("div", class_="sample-tests").findAll("div", class_="sample-test"):
        for block in test_block.findChildren("div", recursive=False):

            if "input" in block["class"] or "output" in block["class"]:
                block_test = block.find("pre")

                for br in block_test.find_all("br"):
                    br.replace_with('\n')

                block_test = pretty(markdownify(pretty(block_test.text)))

            if "input" in block["class"]:
                if cur_test["input"] is not None:
                    tests.append(cur_test)
                    cur_test = {"input": block_test, "output": None}
                else:
                    cur_test["input"] = block_test

            elif "output" in block["class"]:
                if cur_test["output"] is not None:
                    tests.append(cur_test)
                    cur_test = {"input": None, "output": block_test}
                else:
                    cur_test["output"] = block_test

    if not all(item is None for item in cur_test.values()):
        tests.append(cur_test)

    problem["tests"] = tests

    return problem


def main(url):
    print("Starting...")
    if not os.path.isdir("cf2md"):
        os.mkdir("cf2md")

    session = Session()

    print("Downloading page...")
    soup = BeautifulSoup(session.get(url).text, "lxml").find("body")

    print("Parsing...")

    with open("cf2md/page.html", 'w', encoding="utf-8") as file:
        file.write(soup.prettify())

    # with open("page.html", 'r', encoding="utf-8") as file:
    #     soup = BeautifulSoup(file.read(), "lxml").find("div", class_="problem-statement")

    with open("cf2md/README.md", 'w', encoding="utf-8") as file:
        for line in (
            "<!-- {{#title ​Сортировки, куча, бинпоиск}} -->",
            "",
            '<h1 align="center">Сортировки, куча, бинпоиск</h1>',
            ""
        ):
            print(line, file=file)

        for problem in soup.findAll("div", class_="problem-statement"):
            problem = problem2md(problem)

            for line in (
                "## {}".format(problem["title"]),
                "",
                "##### Ограничение по времени на тест: {}".format(problem["time_limit"]),
                "##### Ограничение по памяти на тест: {}".format(problem["memory_limit"]),
                "",
                problem["statement"],
                "",
                "### Входные данные",
                problem["input_specification"],
                "",
                "### Выходные данные",
                problem["output_specification"],
                "",
                "### Пример",
                *(
                    itertools.chain.from_iterable(
                        (
                            (
                                "Входные данные",
                                "```cpp",
                                test["input"],
                                "```",
                                "",
                                "Выходные данные",
                                "```cpp",
                                test["output"],
                                "```",
                                ""
                            ) for test in problem["tests"]
                        )
                    )
                ),
                "### [Решение]({}.cpp)".format(problem["title"][:problem["title"].find('.')]),
                "",
                ""
            ):
                print(line, file=file)

            print(problem)

    with open("cf2md/README.md", 'r', encoding="utf-8") as file:
        result = file.read()

    with open("cf2md/README.md", 'w', encoding="utf-8") as file:
        file.write(result.strip() + '\n')


if __name__ == "__main__":
    main("https://codeforces.com/group/dAhOSPf3oD/contest/349149/problems?locale=ru")
