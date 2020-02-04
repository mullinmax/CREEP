tty=$(tty)
echo $tty;
if [ ! $tty = "/dev/tty1" ]
then
	exit;
fi
