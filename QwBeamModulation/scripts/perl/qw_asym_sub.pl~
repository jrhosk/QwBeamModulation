#!/usr/bin/perl
#
# Submits pedestal jobs to the farm.
#
#

use strict;
use warnings;

use Getopt::Long;
use Cwd;

use vars qw($runs $verbose
	    $help $name 
	    $dir $analyzer
	    $pass4 $result);

$result = GetOptions("runs=s"     => \$runs,
		     "verbose"    => \$verbose,
		     "analyzer=s" => \$analyzer,
		     "pass4"      => \$pass4,
		     "help"       => \$help);

if($help){
    usage();
}

if(!$analyzer){
    $analyzer = "/u/home/jhoskins/QwAnalysis/";
    print "using $analyzer to process data.\n";
}

print "using $analyzer to process data.\n";

my @range = GetRuns($runs);

$name = getpwuid($<);
if(!$pass4){
    $dir = getcwd();
}
else{
    $dir = "/u/home/jhoskins/QwAnalysis/Extensions/Regression/QwBeamModulation";
}

foreach(@range){

    my $output;

    next if( ($_ % 5) != 0);

    $output .= "PROJECT: qweak\n";
    $output .= "TRACK: analysis\n";
    $output .= "JOBNAME: pedestal\n";
    $output .= "OS: Linux64\n";
    $output .= "MEMORY: 1800 MB\n";
    $output .= "COMMAND:sh $dir\/pedestal.bash $_ $analyzer > pedestal$_.out\n";
#    $output .= "INPUT_FILES: /mss/hallc/qweak/rootfiles/pass4b/*$_*\n";
    $output .= "OUTPUT_DATA: pedestal$_.out\n";
    $output .= "OUTPUT_TEMPLATE:$dir\/log\/pedestal$_.out\n";
    $output .= "MAIL: $name\@jlab.org\n";

    open(OUT, ">bmod.config") or die "Can't open file descriptor 'OUT': $!\n";
    if($verbose){
	print $output;
    }
    print OUT $output;
    close(OUT);
    system("jsub bmod.config");
    undef $output;
}


sub GetRuns {
    my $temp = $_[0];
    my @run_range;

    if($temp =~/[.\d]+\:[.\d]/){
        @run_range = split(/\:/,$temp);
	my @range_temp;

	@range_temp = ($run_range[0] .. $run_range[-1]);

	return @range_temp;
    }
    elsif($temp =~ /^[.\d]+$/){
	@run_range = $temp;
	return @run_range;
    }
    elsif($temp =~ /,/){
	@run_range = split(/,/, $temp);
	return @run_range;
    }
    else{
	die("You must specify a run range.  --help for more info");
    }
} 

sub usage{
    print "./qw_jsub_bm.pl <options>";
    print "\n\t--runs <run range>     1234:4321 or 1234,5678 or 1234";
    print "\n\t--analyzer             location of analyzer, ie. \$QWANALYSIS";
    print "\n\t--verbose              more print messages." ;
    print "\n\t--pass4                Use standard analyzer.  This is for pass4b, otherwise it uses working directory.";
    print "\n\t--help                 help!\n";

    exit;
}
