import textwrap
citationHeading = "/* -------------------- Works Cited -------------------- */\n"

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
                   "url retrieved date": "2022 June 03" },

                { "short form"        : "Parahar, 2020",
                   "authors"          : "Parahar, Mahesh",
                   "date"             :  "2020",
                   "title"            :  "Difference between const char* p, char * const p, and const char * const p in C",
                   "publisher"        :  "Tutorialspoint",
                   "url"              :  "https://www.tutorialspoint.com/difference-between-const-char-p-char-const-p-and-const-char-const-p-in-c",
                   "url retrieved date": "2022 June 09" },

                { "short form"        : "Berger, 2012",
                   "authors"          : "Berger, Avi",
                   "date"             :  "2012",
                   "title"            :  "Why structs cannot be assigned directly?: Answer",
                   "publisher"        :  "Stackoverflow",
                   "url"              :  "https://stackoverflow.com/questions/12189480/why-structs-cannot-be-assigned-directly",
                   "url retrieved date": "2022 June 03" },


                { "short form"        : "Python Software Foundation, 2022",
                   "authors"          : "Python Software Foundation",
                   "date"             :  "2022",
                   "title"            :  "textwrap — Text wrapping and filling",
                   "publisher"        :  "Python.org",
                   "url"              :  "https://docs.python.org/3/library/textwrap.html",
                   "url retrieved date": "2022 June 12" }

                   ]



import os
files = os.listdir()
for f in files:
    if f.split(".")[-1] == "c" or f.split(".")[-1] == "h":
        print(f)
        inputfile = open(f, "r")
        lines = inputfile.readlines()
        outputString = ""

        citationsInFileShort = set()
        for line in lines:
            if line == citationHeading:
                break;
            outputString = outputString + line
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
            output = open(f+"_cite", "w")
            output.write(outputString)
            output.write(citationHeading);
            output.write("/* \n")
            for c in citationsInFile:
                if "url" in c:

                    citationString =  "{:}. ({:}). \"{:}.\" {:}.  Retrieved from {:} on {:}.\n".format( c["authors"], c["date"], c["title"], c["publisher"], c["url"], c["url retrieved date"] )
                    citationString = textwrap.wrap( citationString, width=60, initial_indent=" * ", subsequent_indent=" *      " )
                    s=""
                    for t in citationString:
                        s=s+t+"\n";
                    citationString = s
                    
                    output.write( citationString )
                    print(citationString)
                if "ISBN" in c:
                    citationString =  "{:}. ({:}). \"{:}.\" {:}.  ISBN {:}.\n".format( c["authors"], c["date"], c["title"], c["publisher"], c["ISBN"] ) 
                    citationString = textwrap.wrap( citationString, width=60, initial_indent=" * ", subsequent_indent=" *      " )
                    
                    s=""
                    for t in citationString:
                        s=s+t+"\n";
                    citationString = s
                    output.write( citationString )
                    print(citationString)
            output.write(" */\n")
            output.close()
            inputfile.close()
            os.replace( f+"_cite", f)

