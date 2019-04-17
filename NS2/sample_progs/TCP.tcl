set ns [new Simulator]

$ns color 1 Blue

set nf [open out.nam w]
$ns namtrace-all $nf

proc finish {} {
global ns nf
$ns flush-trace
close $nf
exec nam out.nam &
exit 0
}

set n0 [$ns node]
set n1 [$ns node]

$ns duplex-link $n0 $n1 1Mb 100ms DropTail

set tcp [new Agent/TCP]
#$tcp set class_ 2
$ns attach-agent $n0 $tcp
set sink [new Agent/TCPSink]
$ns attach-agent $n1 $sink
$ns connect $tcp $sink
$tcp set fid_ 1

#Setup a FTP over TCP connection
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ftp set type_ FTP

$ns at 0.5 "$ftp start"
$ns at 2.0 "$ftp stop"
#$ns at 2.6 "$ns detach-agent $n0 $tcp ; $ns detach-agent $n1 $sink"
$ns at 2.5 "finish"
$ns run







