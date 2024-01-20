<b>pipex</b>

Your program will be executed as follows: ./pipex file1 cmd1 cmd2 file2<br>
It must take 4 arguments:<br>
• file1 and file2 are file names.<br>
• cmd1 and cmd2 are shell commands with their parameters.<br>

Example:<br>
$> ./pipex infile "ls -l" "wc -l" outfile<br>
Should behave like: < infile ls -l | wc -l > outfile<br>
$> ./pipex infile "grep a1" "wc -w" outfile<br>
Should behave like: < infile grep a1 | wc -w > outfile<br>


<b>pipex</b>

• Handle multiple pipes.<br>
This:<br>
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2<br>
Should behave like:<br>
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2<br>

• Support « and » when the first parameter is "here_doc".<br>
This:<br>
$> ./pipex here_doc LIMITER cmd cmd1 file<br>
Should behave like:<br>
cmd << LIMITER | cmd1 >> file<br>
