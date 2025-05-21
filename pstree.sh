ps aux | grep minishell
watch -n 1 "pstree -p $(pgrep -f minishell)"
strace -f -e trace=clone,fork,vfork,execve,wait4 -o trace.txt bash -c 'cd /tmp'

# /tmp/minishell_rkitao$ echo $USER a
# tohbu a

# /tmp/minishell_rkitao$ echo $"USER a"
# $USER a

# /tmp/minishell_rkitao$ echo $
# $

# /tmp/minishell_rkitao$ echo $""
# $

# /tmp/minishell_rkitao$ echo $''
# $