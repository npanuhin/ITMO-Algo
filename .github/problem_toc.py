import json
import sys
import re


if __name__ == "__main__":
    if len(sys.argv) > 1:  # we check if we received any argument
        if sys.argv[1] == "supports":
            # then we are good to return an exit status code of 0, since the other argument will just be the renderer's name
            exit()

    # load both the context and the book representations from stdin
    context, book = json.load(sys.stdin)
    # and now, we can just modify the content of the first chapter
    # book['sections'][0]['Chapter']['content'] = '# Hello'
    # with open("test.json", 'w') as file:
    #     file.write(json.dumps(book, ensure_ascii=False))
    # we are done with the book's modification, we can just print it to stdout,

    for section in book["sections"]:
        if "Chapter" not in section:
            continue

        chapter = section["Chapter"]

        match = re.search(r"<!--\s*toc\s*\[(.+)\]\s*-->", chapter["content"], flags=re.IGNORECASE | re.UNICODE)
        if match is None:
            continue

        chapter["content"] = chapter["content"][:match.start()] + \
            "<div id=\"toc\"><ul>" + "".join(
            "<li>{}</li>".format(name.strip()) for name in match.group(1).split(',')
        ) + "</ul></div>" + chapter["content"][match.end():]

    print(json.dumps(book, ensure_ascii=False))
