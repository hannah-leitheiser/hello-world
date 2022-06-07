citations = [  { "short form"         : "WG14, 2018",
                 "authors"            : "WG14",
                 "date"               : "2018",
                 "title"              : "Programming Languages -- C. 9899:202x (E)",
                 "publisher"          : "ISO/IEC",
                 "url"                : "https://www.open-std.org/jtc1/sc22/wg14/www/docs/n2310.pdf",
                 "url retrieved date" : "2022 June 03" },
                { "short form"        : "Kernighan & Ritchie, 1988",
                  "authors"           : "Kernighan, Brian W. & Ritchie, Dennis M.",
                  "date"              : "1988", 
                  "title"             : "The C Programming Language, Second Edition.",
                  "publisher"         : "Prentise Hall.",
                  "ISBN"              : "0-13-110370-9" },
                { "short form"        : "Thompson, 2012",
                   "authors"          : "Thompson, Keith",
                   "date"             :  "2012",
                   "title"            :  "Should I return EXIT_SUCCESS or 0 from main()?: Answer",
                   "publisher"        :  "Stack Overflow.",
                   "url"              :  "https://stackoverflow.com/questions/8867871/should-i-return-exit-success-or-0-from-main",
                   "url retrieved date": "2022 June 03" } ]



import os
files = os.listdir()
for f in files:
    if f.split(".")[-1] == "c" or f.split(".")[-1] == "h":
        print(f)
        inputfile = open(f, "r")
        lines = inputfile.readlines()
        output = open(f+"_cite", "w")
        citationsInFileShort = set()
        for line in lines:
            if line == " /* Works Cited */\n":
                break;
            output.write(line)
            for c in citations:
                if c["short form"] in line:
                    citationsInFileShort.add(c["short form"])
        citationsInFile = []
        for c in citations:
            if c["short form"] in citationsInFileShort:
                citationsInFile.append(c)

        citationsInFile = list(citationsInFile)
        citationsInFile.sort( key = lambda x : x["authors"] )
        if len(citationsInFile) > 0:
            output.write(" /* Works Cited */\n");
            output.write(" /* \n")
            for c in citationsInFile:
                if "url" in c:
                    output.write( "{:}. ({:}). \"{:}.\" {:}.  Retrieved from {:} on {:}.\n".format( c["authors"], c["date"], c["title"], c["publisher"], c["url"], c["url retrieved date"] ) )

                if "ISBN" in c:
                    output.write( "{:}. ({:}). \"{:}.\" {:}.  ISBN {:}.\n".format( c["authors"], c["date"], c["title"], c["publisher"], c["ISBN"] ) )
            output.write(" */\n")
            output.close()
            inputfile.close()
            os.replace( f+"_cite", f)

