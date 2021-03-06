#!/usr/bin/perl -w
#
# Parse the errors files aqnd extract values, errors
# into a seperate file.  C++ macro can then be run..
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

use strict;
use warnings;
use Getopt::Long;

use vars qw($line
	    $run_number
	    $slope
	    $error
	    @line
	    @files);

@files = glob('/work/hallc/qweak/QwAnalysis/run1/bmod_regression/slopes_*.dat');


open(OUT, ">monitor_slopes_md8barsum.dat") or die "Couldn't open: $!";

foreach my $file (@files){
    if($file =~/.([\d]+)\.dat/){
	$run_number = $1;
	print "Processing run number: $run_number\n";
    }
    open(IN, "<$file") or die "Couldn't open: $!";
    while(<IN>){
	chomp($_);
	next if ($run_number > 10187);
	if($_ =~/^det qwk_md8barsum/){
	    print OUT "$run_number ";
	    for(my $i = 0; $i < 5; $i++){
		$line = readline( *IN );
		chomp($line);
		@line = split(/\s+/, $line);
		print OUT "$line[0] ";
	    }
	    print OUT "\n";
	}
    }
    close(IN);
}
close(OUT);

