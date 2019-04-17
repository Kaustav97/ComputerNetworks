set ns [new Simulator -multicast on]

$ns color 1  Blue
$ns color 2  Red

#set trace [open test19.tr w]
#$ns trace-all $trace

set namtrace [open test20.nam w]
$ns namtrace-all $namtrace

# allocate a multicast address
set group [Node allocaddr] 

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]
set n5 [$ns node]
set n6 [$ns node]
set n7 [$ns node]
set n8 [$ns node]
set n9 [$ns node]
set n10 [$ns node]
set n11 [$ns node]

$ns duplex-link $n0 $n2 2Mb 10ms RED
$ns duplex-link $n0 $n3 2Mb 10ms RED
$ns duplex-link $n0 $n4 1.7Mb 20ms RED
$ns duplex-link $n0 $n5 1.5Mb 15ms RED
$ns duplex-link $n0 $n6 1.5Mb 15ms RED
$ns duplex-link $n0 $n1 1.5Mb 15ms RED

$ns duplex-link $n1 $n7 1.5Mb 15ms RED
$ns duplex-link $n1 $n8 1.5Mb 15ms RED
$ns duplex-link $n1 $n9 1.5Mb 15ms RED
$ns duplex-link $n1 $n10 1.5Mb 15ms RED
$ns duplex-link $n1 $n11 1.5Mb 15ms RED

set mproto DM ;# configure multicast protocol
set mrthandle [$ns mrtproto $mproto] ;# all nodes will contain multicast protocol agents

set udp [new Agent/UDP] ;# create a source agent at node 0
$ns attach-agent $n10 $udp
set src [new Application/Traffic/CBR]
$src attach-agent $udp
$udp set dst_addr_ $group
$udp set dst_port_ 0
$udp set fid_ 2

set rcvr [new Agent/LossMonitor] ;# create a receiver agent at node 1
$ns attach-agent $n2 $rcvr

$ns at 0.3 "$n2 join-group $rcvr $group" ;
$ns at 0.3 "$n3 join-group $rcvr $group" ;
$ns at 0.3 "$n4 join-group $rcvr $group" ;
$ns at 0.3 "$n5 join-group $rcvr $group" ;
$ns at 0.3 "$n6 join-group $rcvr $group" ;

$ns at 2.0 "$src start"
$ns at 5.0 "$src stop"
proc finish {} {
global ns namtrace #trace
$ns flush-trace
close $namtrace ; #close $trace
exec nam test20.nam &
exit 0
}

$ns at 10.0 "finish"
$ns run
