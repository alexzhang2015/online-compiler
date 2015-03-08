	<?php
	$filelock="Mutex";
	while($filelock=="Mutex")
	{
	$lock=fopen("/var/www/output/filelock","r");
	if($lock){
	$filelock=fgets($lock,6);
	echo $filelock;
	}
	sleep(1);
	fclose($lock);
	}
	?>
