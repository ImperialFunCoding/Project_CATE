#curl --user cmy14 https://cate.doc.ic.ac.uk/personal.cgi?keyp=2014:cmy14
import fileinput
import os

def split_html(html):
    #lineNo      = 0
    tagStack    =[]
    contentStack =[]
    stringStack = ''
    for line in html.split('\n'):
        line = line.strip()
        #lineNo+=1
        i=0
        while i<len(line):
            stringStack+=line[i]
            if(line[i] == '\\' and i<len(line)):
                stringStack+=line[i+1]
                i += 1
            elif(line[i] == '<'):
                contentStack.append(stringStack[:-1])
                stringStack = '<'
            elif(line[i] == '>'):
                tagStack.append(stringStack)
                stringStack = ''
            i += 1
    del contentStack[0]
    tagStack=map(str.strip,tagStack)
    contentStack=map(str.strip,contentStack)
    return (tagStack,contentStack)

def del_empty_html(tags,contents):
    i=0
    cp_t=tags
    cp_c=contents
    while i<len(contents):
        if(contents[i]==''):
            cp_t[i]=''
        i+=1
    while '' in cp_t:
        cp_t.remove('')
        cp_c.remove('')
    return (cp_t,cp_c)
def name_of_tag(tag):
    name=''
    for c in tag[1:]:
        if(c==" " or c==">"):
            return name
        name+=c

print "Input your username for cate:"
username = raw_input()
command  = ("curl --user "
              +username + " "
              +"\"https://cate.doc.ic.ac.uk/timetable.cgi"
              +"?period=1&class=c1&keyt=2014%3Anone%3Anone%3A"
              +username+"\"")
print command
cateHTML = os.popen(command).read();
(tags,contents)=split_html(cateHTML)
(tags,contents)=del_empty_html(tags,contents)

print contents
currentM=""
modules = []
ass     = []
for i in range(0,len(contents)):
    if(contents[i][0] == '-'):
        currentM=contents[i][2:]
        modules.append(currentM)
    elif(contents[i][0] in map(str,range(1,9))):
        nt = name_of_tag(tags[i+1])
        if(nt=="a" or nt=="/b"):
            ass.append((currentM,contents[i+1]))

"""
print modules
print ass
"""
