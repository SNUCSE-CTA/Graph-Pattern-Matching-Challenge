# compile file
cmake ..
make


########### HPRD
#
#mkdir -p ../OUT/HPRD
#
#echo "HPRD_N"
#for i in 1 3 5 8; do
#    timeout 60s ./main/program ../data/lcc_hprd.igraph ../query/lcc_hprd_n${i}.igraph ../candidate_set/lcc_hprd_n${i}.cs > ../OUT/HPRD/lcc_hprd_n${i}.txt
#    wc -l ../OUT/HPRD/lcc_hprd_n${i}.txt
#done
#
#echo "HPRD_S"
#for i in 1 3 5 8; do
#    timeout 60s ./main/program ../data/lcc_hprd.igraph ../query/lcc_hprd_s${i}.igraph ../candidate_set/lcc_hprd_s${i}.cs > ../OUT/HPRD/lcc_hprd_s${i}.txt
#    wc -l ../OUT/HPRD/lcc_hprd_s${i}.txt
#done

########### HUMAN

#
#mkdir ../OUT/HUMAN
#
#echo "HUMAN_N"
#for i in 1 3 5 8; do
#    timeout 60s ./main/program ../data/lcc_human.igraph ../query/lcc_human_n${i}.igraph ../candidate_set/lcc_human_n${i}.cs > ../OUT/HUMAN/lcc_human_n${i}.txt
#    wc -l ../OUT/HUMAN/lcc_human_n${i}.txt
#done
#
#echo "HUMAN_S"
#for i in 1 3 5 8; do
#    timeout 60s ./main/program ../data/lcc_human.igraph ../query/lcc_human_s${i}.igraph ../candidate_set/lcc_human_s${i}.cs > ../OUT/HUMAN/lcc_human_s${i}.txt
#    wc -l ../OUT/HUMAN/lcc_human_s${i}.txt
#done

######### YEAST

mkdir ../OUT/YEAST

echo "YEAST_N"
for i in 1 3 5 8; do
    timeout 60s ./main/program ../data/lcc_yeast.igraph ../query/lcc_yeast_n${i}.igraph ../candidate_set/lcc_yeast_n${i}.cs > ../OUT/YEAST/lcc_yeast_n${i}.txt
    wc -l ../OUT/YEAST/lcc_yeast_n${i}.txt
done

echo "YEAST_S"
for i in 1 3 5 8; do
    timeout 60s ./main/program ../data/lcc_yeast.igraph ../query/lcc_yeast_s${i}.igraph ../candidate_set/lcc_yeast_s${i}.cs > ../OUT/YEAST/lcc_yeast_s${i}.txt
    wc -l ../OUT/YEAST/lcc_yeast_s${i}.txt
done

