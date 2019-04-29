# INDEX 
cat LHS.txt | tr 'qazwsxedcfrvtgb' 'yhnujmik,ol.p;/' > RHS_TR.txt
echo "same pos"
comm -12 RHS_TR.txt RHS.txt
cat LHS.txt | tr 'qazwsxedcfrvtgb' 'p;/ol.ik,ujmyhn' > RHS_MIRR.txt
echo "MIRR pos"
comm -12 RHS_MIRR.txt RHS.txt