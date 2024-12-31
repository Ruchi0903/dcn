set ns [new Simulator]

# Open trace and NAM files
set ntrace [open prog2.tr w]
$ns trace-all $ntrace

set namfile [open prog2.nam w]
$ns namtrace-all $namfile

proc Finish {} {
    global ns ntrace namfile
    $ns flush-trace
    close $ntrace
    close $namfile
    exec nam prog2.nam &
    exec echo "The number of TCP packets sent are" &
    exec grep "^+" prog2.tr | cut -d " " -f 5 | grep -c "tcp" &
    exec echo "The number of UDP packets sent are" &
    exec grep "^+" prog2.tr | cut -d " " -f 5 | grep -c "cbr" &
    exit 0
}

# Create nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

# Create links
$ns duplex-link $n0 $n2 2Mb 10ms DropTail
$ns duplex-link $n1 $n2 2Mb 10ms DropTail
$ns duplex-link $n2 $n3 2Mb 20ms DropTail

# Add visual orientation for links in NAM
$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link-op $n2 $n3 orient right

$n0 label "TCP Source"
$n1 label "UDP Source"
$n3 label "Destination"
$n0 color blue
$n1 color orange
$n3 color red

# Set up TCP connection
set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
set sink0 [new Agent/TCPSink]
$ns attach-agent $n3 $sink0
$ns connect $tcp0 $sink0

# Set up UDP connection
set udp0 [new Agent/UDP]
$ns attach-agent $n1 $udp0
set null0 [new Agent/Null]
$ns attach-agent $n3 $null0
$ns connect $udp0 $null0

# Applications over TCP and UDP
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

set cbr0 [new Application/Traffic/CBR]
$cbr0 set type_ CBR
$cbr0 set packetSize_ 1000
$cbr0 set rate_ 0.01Mb
$cbr0 set random_ false
$cbr0 attach-agent $udp0

# Schedule events
$ns at 0.1 "$cbr0 start"
$ns at 1.5 "$ftp0 start"
$ns at 1.0 "$cbr0 stop"
$ns at 2.5 "$ftp0 stop"
$ns at 5.0 "Finish"

# Run the simulation
$ns run
