const toc = document.getElementById("toc");

if (toc !== null) {
    document.getElementById("page-wrapper").prepend(toc);

    const toc_headers = toc.getElementsByTagName("li"),
          headers = document.querySelectorAll("main > h2");

    for (let i = 0; i < Math.min(toc_headers.length, headers.length); i++) {
        toc_headers[i].innerHTML = '<a href="#' + headers[i].id + '">' + toc_headers[i].innerHTML + '</a>';

        toc_headers[i].getElementsByTagName("a")[0].addEventListener("click", function (e){
            e.preventDefault();
            
            const target = this.getAttribute("href");

            window.scrollTo({
                top: document.querySelector(target).offsetTop - 70,
                behavior: "smooth"
            });

            const url = new URL(location.href);
            url.hash = target;
            history.replaceState({}, '', url);
        });
    }

    toc.style.display = "block";
}
