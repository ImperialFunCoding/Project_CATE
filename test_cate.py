import fileinput
def concat(ls):
    return ''.join(ls)
lineNo      = 0
tagStack    =[]
contentStack =[]
for line in fileinput.input("test.html"):
    line = line.strip()
    lineNo+=1
    stringStack = []
    for char in line:
        if(char == '<'):
            contentStack.append(concat(stringStack))
            stringStack = []
            stringStack.append(char)
        elif(char == '>'):
            stringStack.append(char)
            tagStack.append(concat(stringStack))
            stringStack = []
        else:
            stringStack.append(char)

del contentStack[0]

print tagStack
print contentStack
