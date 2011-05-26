#!/usr/bin/perl -w
use strict;

sub usage
{
	my ($arg) = @_ ;
	die "'$arg' must be an existing file.\n";
}

sub main
{
	my $file = $ARGV[0];

	if (!(-e $file) || -d $file)
	{
		usage($file);
	}

	my $contents;
	open FH, "< $file";

	while (my $line = <FH>)
	{
		$contents .= $line;
	}

	$contents =~ s/\/\*\$.*?\$\*\///gs;
	$contents =~ s/^\h*(\r|\n)*//;
	$contents =~ s/\h+$//g;
	$contents =~ s/^\h*(\r|\n)*h*$//gm;
	$contents =~ s/\t/  /g;

	print $contents;

	close(FH);

	return 0;
}

main();
