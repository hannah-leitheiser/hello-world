import textwrap

citationHeading = "/* --------------------- Works Cited -------------------- */\n"
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
                  "title"             : "The C Programming Language, Second Edition",
                  "publisher"         : "Prentise Hall",
                  "ISBN"              : "0-13-110370-9" },
                { "short form"        : "Thompson, 2012",
                   "authors"          : "Thompson, Keith",
                   "date"             :  "2012",
                   "title"            :  "Should I return EXIT_SUCCESS or 0 from main()?: Answer",
                   "publisher"        :  "Stack Overflow.",
                   "url"              :  "https://stackoverflow.com/questions/8867871/should-i-return-exit-success-or-0-from-main",
                   "url retrieved date": "2022 June 03" },

                { "short form"        : "GeeksforGeeks et. al., 2022",
                   "authors"          : "GeeksforGeeks, KartheekMudarakola, adnanirshad158, & tarun18tk",
                   "date"             :  "2022",
                   "title"            :  "Enumeration (or enum) in C",
                   "publisher"        :  "GeeksforGeeks.org",
                   "url"              :  "https://www.geeksforgeeks.org/enumeration-enum-c/",
                   "url retrieved date": "2022 June 23" },


                { "short form"        : "GeeksforGeeks, 2018",
                   "authors"          : "GeeksforGeeks",
                   "date"             :  "2018",
                   "title"            :  "Function Pointer in C",
                   "publisher"        :  "GeeksforGeeks.org",
                   "url"              :  "https://www.geeksforgeeks.org/function-pointer-in-c/",
                   "url retrieved date": "2022 June 23" },


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

                { "short form"        : "Fisher, 2016",
                   "authors"          : "Fisher, James",
                   "date"             :  "2016",
                   "title"            :  "How do I write a multi-line string literal in C?",
                   "publisher"        :  "Website",
                   "url"              :  "https://jameshfisher.com/2016/11/30/c-multiline-literal/",
                   "url retrieved date": "2022 June 14" },

                { "short form"        : "Parewa Labs, n.d., C struct",
                   "authors"          : "Parewa Labs",
                   "date"             :  "n.d.",
                   "title"            :  "C struct",
                   "publisher"        :  "Parewa Labs Pvt. Ltd.",
                   "url"              :  "https://www.programiz.com/c-programming/c-structures",
                   "url retrieved date": "2022 June 14" },


                { "short form"        : "Parewa Labs, n.d., C strcmp()",
                   "authors"          : "Parewa Labs",
                   "date"             :  "n.d.",
                   "title"            :  "C strcmp()",
                   "publisher"        :  "Parewa Labs Pvt. Ltd.",
                   "url"              :  "https://www.programiz.com/c-programming/library-function/string.h/strcmp",
                   "url retrieved date": "2022 June 14" },

                { "short form"        : "Tutorials Point, 2022",
                   "authors"          : "Tutorials Point",
                   "date"             :  "2022",
                   "title"            :  "C library function - exit()",
                   "publisher"        :  "Tutorials Point",
                   "url"              :  "https://www.tutorialspoint.com/c_standard_library/index.htm",
                   "url retrieved date": "2022 June 14" },

                { "short form"        : "Python Software Foundation, 2022",
                   "authors"          : "Python Software Foundation",
                   "date"             :  "2022",
                   "title"            :  "textwrap — Text wrapping and filling",
                   "publisher"        :  "Python.org",
                   "url"              :  "https://docs.python.org/3/library/textwrap.html",
                   "url retrieved date": "2022 June 12" }

                   ,

                { "short form"        : "cschol, 2008",
                   "authors"          : "cschol",
                   "date"             :  "2008",
                   "title"            :  "Organization of C files: Answer",
                   "publisher"        :  "Stackoverflow",
                   "url"              :  "https://stackoverflow.com/questions/47919/organization-of-c-files",
                   "url retrieved date": "2022 June 03" },


                { "short form"        : "Walia et. al., n.d.",
                   "authors"          : "Walia, D., Jonny, Goel, R., & Yogesh",
                   "date"             :  "n.d.",
                   "title"            :  "C read file",
                   "publisher"        :  "Programmingsimplified",
                   "url"              :  "https://www.programmingsimplified.com/c-program-read-file",
                   "url retrieved date": "2022 June 20" },


                { "short form"        : "Borini & Smith, 2009",
                   "authors"          : "Smith, Jed & Borini, Stefano",
                   "date"             :  "2009",
                   "title"            :  "What do .c and .h file extensions mean to C?, Answer",
                   "publisher"        :  "Stackoverflow",
                   "url"              :  "https://stackoverflow.com/questions/1695224/what-do-c-and-h-file-extensions-mean-to-c",
                   "url retrieved date": "2022 June 03" },

                { "short form"        : "mbaotpff & gsamaras, 2018",
                   "authors"          : "mbaitoff & gsamaras",
                   "date"             :  "2018",
                   "title"            :  "C read file line by line: Answer",
                   "publisher"        :  "Stackoverflow",
                   "url"              :  "https://stackoverflow.com/questions/3501338/c-read-file-line-by-line",
                   "url retrieved date": "2022 June 20" },

                { "short form"        : "Jester-Young, 2010",
                   "authors"          : "Jester-Young, Chris",
                   "date"             :  "2010",
                   "title"            :  "Using true and false in C: Answer",
                   "publisher"        :  "Stackoverflow",
                   "url"              :  "https://stackoverflow.com/questions/2254075/using-true-and-false-in-c",
                   "url retrieved date": "2022 June 18" },

                { "short form"        : "Brouwer, 2001",
                   "authors"          : "Brouwer, Andries",
                   "date"             :  "2001",
                   "title"            :  "asprintf(3) — Linux manual page",
                   "publisher"        :  "GNU Linux",
                   "url"              :  "https://man7.org/linux/man-pages/man3/asprintf.3.html",
                   "url retrieved date": "2022 June 25" },

                { "short form"        : "Koenig & Kerrisk, 2018",
                   "authors"          : "Koenig, Thomas & Kerrisk, Michael",
                   "date"             :  "2018",
                   "title"            :  "malloc(3) — Linux manual page",
                   "publisher"        :  "GNU Linux",
                   "url"              :  "https://man7.org/linux/man-pages/man3/malloc.3.html",
                   "url retrieved date": "2022 July 14" },

                { "short form"        : "Stackoverflow, 2022",
                   "authors"          : "Stackoverflow",
                   "date"             :  "2022",
                   "title"            :  "sprintf function's buffer overflow?",
                   "publisher"        :  "Stackoverflow",
                   "url"              :  "https://stackoverflow.com/questions/4282281/sprintf-functions-buffer-overflow",
                   "url retrieved date": "2022 June 18" },


                { "short form"        : "IEEE, Inc & The Open Group, 2018",
                   "authors"          : "Institute of Electrical and Electronics Engineers, Inc, & The Open Group",
                   "date"             :  "2018",
                   "title"            :  "stdbool.h(0p) — Linux manual page",
                   "publisher"        :  "GNU Linux",
                   "url"              :  "https://man7.org/linux/man-pages/man0/stdbool.h.0p.html",
                   "url retrieved date": "2022 July 16" },




                { "short form"        : "cppreference.com, 2020",
                   "authors"          : "cppreference.com",
                   "date"             :  "2020",
                   "title"            :  "va_list",
                   "publisher"        :  "cppreference.com",
                   "url"              :  "https://en.cppreference.com/w/c/variadic/va_list",
                   "url retrieved date": "2022 July 16" },


                { "short form"        : "cppreference.com, 2020, va_start",
                   "authors"          : "cppreference.com",
                   "date"             :  "2020",
                   "title"            :  "va_start",
                   "publisher"        :  "cppreference.com",
                   "url"              :  "https://en.cppreference.com/w/c/variadic/va_start",
                   "url retrieved date": "2022 July 16" },


                { "short form"        : "Karpov, 2008",
                   "authors"          : "Andrey Karpov",
                   "date"             :  "2008",
                   "title"            :  "Building of systems of automatic C/C++ code logging",
                   "publisher"        :  "PVS-Studio",
                   "url"              :  "https://pvs-studio.com/en/blog/posts/a0023/",
                   "url retrieved date": "2022 June 16" }


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

