set ns [new Simulator]
set f [open out.tr w]
$ns trace-all $f
set nf [open out.nam w]
$ns namtrace-all $nf

$ns color 1 blue
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$n0 color green
$n0 shape square
$n1 color blue

$ns duplex-link $n0 $n1 1mb 10ms RED
$ns duplex-link $n1 $n2 1mb 10ms RED
$ns duplex-link $n0 $n2 1mb 10ms RED

$ns duplex-link-op $n0 $n2 color blue
$ns duplex-link-op $n1 $n0 orient right

set tcp [new Agent/TCP]
set sink [new Agent/TCPSink]
$ns attach-agent $n0 $tcp
$ns attach-agent $n1 $sink
$ns connect $tcp $sink
set ftp [new Application/FTP]
$ftp attach-agent $tcp
$tcp set fid_	1

proc finish {} {
 global ns nf f
 $ns flush-trace
 close $nf
 exec nam out.nam &
 exit 0
}

$ns rtmodel-at  1.0 down $n0
$ns rtmodel-at  3.0 up $n0
$ns at 0.5 "$ftp start"
$ns at 1.5 "$ftp stop"
$ns at 5.0 "finish"
$ns run



