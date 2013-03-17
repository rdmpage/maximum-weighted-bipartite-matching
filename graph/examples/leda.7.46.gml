graph [
comment "Graph from Fig. 7.46 of LEDA book. It has a mincut value of 47"
directed 0

node [ id 0 label "0" graphics [fill "#000000"] LabelGraphics [type "text" fill "#ffffff"] ]
node [ id 3 label "3" graphics [type "oval" fill "#000000"]  LabelGraphics [type "text" fill "#ffffff"] ]
node [ id 4 label "4" graphics [fill "#000000"] LabelGraphics [type "text" fill "#ffffff"] ]
node [ id 5 label "5" graphics [fill "#000000"] LabelGraphics [type "text" fill "#ffffff"] ]
node [ id 6 label "6" graphics [fill "#000000"] LabelGraphics [type "text" fill "#ffffff"] ]
node [ id 7 label "7" graphics [type "oval" fill "#000000"] LabelGraphics [type "text" fill "#ffffff"] ]

edge [ source 0 target 3 weight 13 label "13"]
edge [ source 0 target 4 weight 12 label "12"]
edge [ source 0 target 7 weight 8 label "8"]
edge [ source 0 target 6 weight 71 label "71"]
edge [ source 3 target 7 weight 84 label "84"]
edge [ source 3 target 6 weight 8 label "8"]
edge [ source 4 target 7 weight 18 label "18"]
edge [ source 4 target 6 weight 11 label "11"]
edge [ source 4 target 5 weight 51 label "51"]
edge [ source 5 target 6 weight 87 label "87"]
 
]