Project\_CATE
============

## Preface

Hello to all you hackers out there, we are Jason and Amey, computing students at Imperial College London. The main motivation behind this project was to write an interface which made accessing CATE (an online course management system for DOC) and using its functionality easier.

This program has been written in C++.

## What is the latest version?
CATE beta2

## How do I install it?

1. Go to [https://github.com/ImperialUndergroundHacker/Project_CATE/releases/tag/beta2](Go to https://github.com/ImperialUndergroundHacker/Project_CATE/releases/tag/beta2) and download the latest release.

2. Extract your files

3. Run `make install` to compile and install cate

## How do I call the program without "./" in front of "cate"?

There are two ways that we recommend to make the "cate" command recognisable by your machine.

### Build an alias (works for the lab machines)

To build an alias, perform the following command on the terminal:

Linux:
```bash
--Pre: the cate program is in your current directory
> echo "alias cate $(pwd)/bin/cate" >> ~/.cshrc
> source ~/.cshrc
```

Mac:
```bash
--Pre: the cate program is in your current directory
> echo "alias cate=$(pwd)/bin/cate" >> ~/.bash_profile
> source ~/.bash_profile
```

### Copy it to a directory in your path

Your unix terminal has a list of directories under which is should search for binaries. If you
either add the `./bin` path of Project\_CATE to your path variable, or move the binary to a directory
that is already in your path, then you will be able to run the command without the `./` prefix.

Alternatively, `make install` should do this for you. If that doesn't work, then likely you're
either missing a `/usr/local/bin` folder, or that directory is not in your `PATH`. Please see
[here](http://www.linfo.org/path_env_var.html) for more information on how to fix this.
This command will require your computer password.

## How do I use CATE?

All possible cate commands:

### cate update

Updates your computer with the latest changes on cate, for example if a new assignment has been uploaded.

### cate set &lt;class&gt; &lt;period&gt;

Sets your current class and period.

#### period table

| Period | Meaning     |
|--------|-------------|
| 1      | AUTUMN TERM |
| 2      | Christmas   |
| 3      | SPRING TERM |
| 4      | Easter      |
| 5      | SUMMER TERM |
| 6      | Jun-Jul     |
| 7      | Aug-Sept    |

- e.g. for Computing first year in autumn, type into terminal:
```bash
> cate set c1 1
```

- e.g. for JMC third year in spring, type into terminal:
```bash
> cate set j3 3
```

### cate ass
Lists the assignments for which the deadline has not passed, with their IDs and due date.

### cate ass -a
Lists all the assignments which are available on cate along with their IDs.

### cate mods
Lists all the modules for the current term, along with their module numbers.

### cate mods &lt;modnumber&gt;
Lists all the notes available for a specific module, along with the IDs.
- e.g. type into terminal:
```bash
> cate mods 3
```

### cate pull [&lt;id&gt;]
Downloads files to your current directory, and asks you if you want to print them. Input the IDs of the files you wish to download.
- e.g. To download files with IDs s502, s545 and n19, type into terminal:
```bash
> cate pull s502 s545 n19
```

### cate submit &lt;id&gt;
Submits a programming assignment to cate. Right after you push your work, just run this command from your assignment's folder, and it will handle the declaration submission and cate token upload.

### cate getcover [&lt;id&gt;]
Handles the submission of non-programming assignments. This will download the cover pages and ask you if you want to print them.
- e.g. type into terminal:
```bash
> cate getcover s502 s545
```

## Last words

This app is not an official app from DOC.
Please use it at your own risk. :)

