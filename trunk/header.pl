#!/usr/bin/perl -w
use strict;

sub usage
{
	my ($arg) = @_ ;
	die "'$arg' must be an existing file.\n";
}

sub main
{
	if (scalar(@ARGV) < 2)
	{
		usage("");
	}

	my $file = $ARGV[0];
	my $outfile = $ARGV[1];

	if (!(-e $file) || -d $file)
	{
		usage($file);
	}
	elsif (-d $outfile)
	{
		usage($outfile);
	}

	my $contents = "";

	open FH, "< $file";

	while (my $line = <FH>)
	{
		if ($line =~ m/^% Function rhead: prints the right header/)
		{
			$contents .= "% Function lhead: prints the left header\n";
			$contents .= "/lhead {  %def\n";
			$contents .= "  174 579.25 moveto\n";
			$contents .= "  fHelvetica fnfs 0.8 mul scalefont setfont\n";
			$contents .= "  l-show\n";
			$contents .= "} bind def\n";
			$contents .= "\n";
		}
		elsif ($line =~ m/\(\d+\) rhead/)
		{
			$contents .= "(University of Wisconsin - Madison) lhead\n";
		}
		$contents .= $line;
	}

	close(FH);

	open FH, "> $outfile";

	print FH $contents;

	close(FH);

	return 0;
}

main();

