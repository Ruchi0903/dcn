set ns [new Simulator] 
set trf [open p3.tr w] 
$ns trace-all $trf 
set naf [open p3.nam w] 
$ns namtrace-all $naf 


set n0 [$ns node] 
$n0 color "red" 
$n0 label "Source 1" 
set n1 [$ns node] 
$n1 color "blue" 
$n1 label "Source 2" 
set n2 [$ns node] 
$n2 color "magenta" 
$n2 label "Destination 1" 
set n3 [$ns node] 
$n3 color "green" 
$n3 label "Destination 2" 


set lan [$ns newLan "$n0 $n1 $n2 $n3" 5Mb 10ms LL Queue/DropTail Mac/802_3] 


set tcp [new Agent/TCP] 
$ns attach-agent $n0 $tcp 
set ftp [new Application/FTP] 
$ftp attach-agent $tcp 
set sink [new Agent/TCPSink] 
$ns attach-agent $n2 $sink 
$ns connect $tcp $sink 


set udp [new Agent/UDP] 
$ns attach-agent $n1 $udp 
set cbr [new Application/Traffic/CBR] 
$cbr attach-agent $udp 
set null [new Agent/Null] 
$ns attach-agent $n3 $null 
$ns connect $udp $null


$ns at 0.1 "$cbr start" 
$ns at 2.0 "$ftp start" 
$ns at 1.9 "$cbr stop" 
$ns at 4.3 "$ftp stop" 
$ns at 6.0 "finish"


proc finish {} { 
    global ns naf trf 
    $ns flush-trace 
    exec nam p3.nam & 
    close $trf 
    close $naf 
    exec echo "The number of packet drops due to collision are" & 
    exec grep -c "^d" p3.tr & 
    exit 0 
}

$ns run