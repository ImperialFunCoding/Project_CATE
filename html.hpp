/*
useful command for fetching htmls

personal page
curl --user cmy14 "https://cate.doc.ic.ac.uk/personal.cgi?keyp=2014:cmy14"

timetable
curl --user cmy14 "https://cate.doc.ic.ac.uk/timetable.cgi?period=1&class=c1&keyt=2014%3Anone%3Anone%3Acmy14"

submit declearation
curl -u cmy14 -d "help-0=&help-1=&help-2=&help-3=&help-4=&help-5=&help-6=&help-7=&inLeader=&inMember=&version=0&key=2014:1:23:c1:leader:cmy14" "https://cate.doc.ic.ac.uk/handins.cgi?key=2014:1:23:c1:new:cmy14"

submit cate_token.txt
curl -u cmy14 -F "key=2014:1:23:c1:submit:cmy14" -F "file-516-none=@cate_token.txt" "https://cate.doc.ic.ac.uk/handins.cgi?key=2014:1:23:c1:new:cmy14"
