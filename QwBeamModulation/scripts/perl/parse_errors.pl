#!/usr/bin/perl -w
#
# Parse the errors files aqnd extract values, errors
# into a seperate file.  C++ macro can then be run..
#
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

use strict;
use warnings;

use vars qw($line
	    $run_number
	    $slope
	    $error
	    @line
	    @files);

@files = glob('../slopes/slopes_*.dat');
#@files = glob('../slopes/slopes_11257.dat');

open(MD, ">mdout.dat") or die "Couldn't open: $!";
open(LUMI, ">lumiout.dat") or die "Could not open: $!";

foreach my $file (@files){
    if($file =~/.([\d]+)/){
	$run_number = $1;
	print "Processing run number: $run_number\n";
    }
    open(IN, "<$file") or die "Couldn't open: $!";
    while(<IN>){
	chomp($_);
	if($_ =~/^det\s+(qwk_mdallbars)/){
	    print MD "$run_number ";
	    for(my $i = 0; $i < 5; $i++){
		$line = readline( *IN );
		chomp($line);
		@line = split(/\s+/, $line);
		print MD "$line[0] $line[1] ";
	    }
	    print MD "\n";
	}
	if($_ =~/^det\s+(uslumi_sum)/){
	    print LUMI "$run_number ";
	    for(my $i = 0; $i < 5; $i++){
		$line = readline( *IN );
		chomp($line);
		@line = split(/\s+/, $line);
		print LUMI "$line[0] $line[1] ";
	    }
	    print LUMI "\n";
	}
    }
    close(IN);
}
close(MD);
close(LUMI);
