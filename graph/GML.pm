#
# GML - perl module for writing a Graph as a GML file
#
# $Id: GML.pm,v 1.1 2004/04/14 23:05:37 rdmp1c Exp $
#
# Written by Rod Page, based on code in the Graph::ReadWrite module.
#
#

package GML;

use strict;

use Graph::Writer;
use vars qw(@ISA);
@ISA = qw(Graph::Writer);

#-----------------------------------------------------------------------
# List of valid dot attributes for the entire graph, per node,
# and per edge. You can set other attributes, but they won't get
# written out.
#-----------------------------------------------------------------------
my %valid_attributes =
(
    node  => [qw(label)],
    edge  => [qw(label weight)],
);

#=======================================================================
#
# _write_graph()
#
# The private method which actually does the writing out in
# dot format.
#
# This is called from the public method, write_graph(), which is
# found in Graph::Writer.
#
#=======================================================================
sub _write_graph
{
	my $self  = shift;
	my $graph = shift;
	my $FILE  = shift;

	my $v;
    my %v2n;
    my $node_num;
    my $from;
    my $to;
    my %attributes;
    my @keys;

	print $FILE "graph [\n";
	print $FILE "comment ";
	if ($graph->has_attribute('name'))
	{
		print $FILE "\"", $graph->get_attribute('name'), "\"";
	}
	else
	{
		print $FILE "\"Graph exported by GML.pm\"";
	}
	print $FILE "\n";
		

	print $FILE "directed ", $graph->directed(), "\n";
	
    $node_num = 0;
    foreach $v ($graph->vertices)
    {
		$v2n{$v} = $node_num;
		
		
		print $FILE "node [ id ", $node_num;
		
		%attributes = $graph->get_attributes($v);
		@keys = grep(exists $attributes{$_}, @{$valid_attributes{'node'}});
		if (@keys > 0)
		{
	    	print $FILE " ", join(',', map { "$_ \"$attributes{$_}\"" } @keys), " ";
		}

		
		print $FILE "]\n";
		++$node_num;
    }
	

    my @edges = $graph->edges;
    while (@edges > 0)
    {
		($from, $to) = splice(@edges, 0, 2);
		
		print $FILE "edge [ source ", $v2n{$from}, " target ", $v2n{$to};
		
		%attributes = $graph->get_attributes($from, $to);
		@keys = grep(exists $attributes{$_}, @{$valid_attributes{'edge'}});
		if (@keys > 0)
		{
			print $FILE " ", join(',', map { "$_ \"$attributes{$_}\"" } @keys), " ";
		}

		
		print $FILE  "]\n";
    }

	
	print $FILE "]\n";
	

   return 1;
}

1;
