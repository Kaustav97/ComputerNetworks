#Create a simulator object
set ns [new Simulator -multicast on]

#Define different colors for data flows (for NAM)
$ns color 1 Blue
$ns color 2 Red

set trace [open test19.tr w]
$ns trace-all $trace

#Open the NAM trace file
set namtrace [open out.nam w]
$ns namtrace-all $namtrace

set group [Node allocaddr]

#Create four nodes
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


#Create links between the nodes
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


#Set Queue Size of link (n2-n3) to 10
#$ns queue-limit $n2 $n3 10
#Give node position (for NAM)

$ns duplex-link-op $n9 $n1 orient right
$ns duplex-link-op $n8 $n1 orient right-down
$ns duplex-link-op $n7 $n1 orient down
$ns duplex-link-op $n10 $n1 orient right-up
$ns duplex-link-op $n11 $n1 orient up

$ns duplex-link-op $n1 $n0 orient right
$ns duplex-link-op $n2 $n0 orient down
$ns duplex-link-op $n0 $n3 orient right-up
$ns duplex-link-op $n0 $n4 orient right
$ns duplex-link-op $n0 $n5 orient right-down
$ns duplex-link-op $n0 $n6 orient down

#Monitor the queue for link (n2-n3). (for NAM)
#$ns duplex-link-op $n2 $n3 queuePos 0.5

set mproto DM
set mrthandle [$ns mrtproto $mproto]

set udp [new Agent/UDP] ;# create a source agent at node 0
$ns attach-agent $n10 $udp
set src [new Application/Traffic/CBR]
$src attach-agent $udp
$udp set dst_addr_ $group
$udp set dst_port_ 0

set rcvr [new Agent/LossMonitor] ;# create a receiver agent at node 1
$ns attach-agent $n6 $rcvr

$ns at 0.3 "$n2 join-group $rcvr $group" ;
$ns at 0.4 "$n3 join-group $rcvr $group" ;
$ns at 0.5 "$n4 join-group $rcvr $group" ;
$ns at 0.6 "$n5 join-group $rcvr $group" ;
$ns at 0.7 "$n6 join-group $rcvr $group" ;


$ns at 2.0 "$src start"
$ns at 5.0 "$src stop"

proc finish {} {
global ns namtrace trace
$ns flush-trace
close $namtrace ; close $trace
exec nam test19.nam &
exit 0
}


$ns at 10.0 "finish"
$ns run




















