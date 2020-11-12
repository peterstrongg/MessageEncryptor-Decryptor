def splitWord():
    file = open("info.txt", 'r')

    str = file.read()
    splitStr = str.split()

    file = open("info.txt", 'w')

    for i in range(len(splitStr)):
        file.write(splitStr[i] + '\n')

    file.close()

splitWord()
