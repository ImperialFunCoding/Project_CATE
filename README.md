Project_CATE
============
##Preface
Hello to all you hackers out there, we are Jason and Amey, computing students at Imperial College London. The main motivation behind this project was to write an interface which made accessing CATE (an online course management system for DOC) and using its functionality easier.

This program has been written in C++.

##What is the latest version?
CATE beta

##How do I install it?
1. Go to [https://github.com/ImperialUndergroundHacker/Project_CATE/releases/tag/beta](Go to https://github.com/ImperialUndergroundHacker/Project_CATE/releases/tag/beta) and download the latest release.

2. Extract your files

Cate is ready on your machine! You can call it using:
```bash
-- Pre: You need to be inside the folder
> ./cate
```

##How do I call the program without "./" in front of "cate"?
There are two ways that we recommend to make the "cate" command recognisable by your machine.
###Build an alias (works for the lab machines)
To build an alias, perform the following command on the terminal:
Linux:
```bash
--Pre: the cate program is in your current directory
> pwd | xargs -i echo "alias cate {}/cate" >> ~/.cshrc
> source ~/.cshrc
```
Mac:
```bash
--Pre: the cate program is in your current directory
> pwd | xargs -i echo "alias cate={}/cate" >> ~/.bash_profile
> source ~/.bash_profile
```
###Copy it to "/bin" (requires sudo)
To copy the file to the "/bin", perform the following command on the terminal:
```bash
--Pre: the compiled cate file is at your current directory
> sudo cp cate /bin
```
This command will require your computer password.

The cate command is now ready to use!
##How do I use CATE?
All possible cate commands:

###cate update
Updates your computer with the latest changes on cate, for example if a new assignment has been uploaded.

###cate set &lt;class&gt; &lt;period&gt;
Sets your current class and period.
- e.g. for Computing first year in autumn, type into terminal:
```bash
> cate set c1 1
```

- e.g. for JMC first year in autumn, type into terminal:
```bash
> cate set j1 1
```

###cate ass
Lists the assignments for which the deadline has not passed, with their IDs and due date.

###cate ass -a
Lists all the assignments which are available on cate along with their IDs.

###cate mods
Lists all the modules for the current term, along with their module numbers.

###cate mods &lt;modnumber&gt;
Lists all the notes available for a specific module, along with the IDs.
- e.g. type into terminal:
```bash
> cate mods 3
```

###cate pull [&lt;id&gt;]
Downloads files to your current directory, and asks you if you want to print them. Input the IDs of the files you wish to download.
- e.g. To download files with IDs s502, s545 and n19, type into terminal:
```bash
> cate pull s502 s545 n19
```

###cate submit &lt;id&gt;
Submits a programming assignment to cate. Right after you push your work, just run this command from your assignment's folder, and it will handle the declaration submission and cate token upload.

###cate getcover [&lt;id&gt;]
Handles the submission of non-programming assignments. This will download the cover pages and ask you if you want to print them.
- e.g. type into terminal:
```bash
> cate getcover s502 s545
```
