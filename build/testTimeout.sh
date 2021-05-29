# compile file
cmake ..
make


########### HPRD

mkdir -p ../OUT/HPRD

echo "HPRD_N"
for i in 1 3 5 8; do
    timeout 30s ./main/program ../data/lcc_hprd.igraph ../query/lcc_hprd_n${i}.igraph ../candidate_set/lcc_hprd_n${i}.cs > ../OUT/HPRD/lcc_hprd_n${i}.txt
    tail -n1 ../OUT/HPRD/lcc_hprd_n${i}.txt | grep -v 'a'
    wc -l ../OUT/HPRD/lcc_hprd_n${i}.txt | awk '{print $1}'
done

echo "HPRD_S"
for i in 1 3 5 8; do
    timeout 30s ./main/program ../data/lcc_hprd.igraph ../query/lcc_hprd_s${i}.igraph ../candidate_set/lcc_hprd_s${i}.cs > ../OUT/HPRD/lcc_hprd_s${i}.txt
    tail -n1 ../OUT/HPRD/lcc_hprd_s${i}.txt | grep -v 'a'
    wc -l ../OUT/HPRD/lcc_hprd_s${i}.txt | awk '{print $1}'
done

########## HUMAN


mkdir ../OUT/HUMAN

echo "HUMAN_N"
for i in 1 3 5 8; do
    timeout 30s ./main/program ../data/lcc_human.igraph ../query/lcc_human_n${i}.igraph ../candidate_set/lcc_human_n${i}.cs > ../OUT/HUMAN/lcc_human_n${i}.txt
    tail -n1 ../OUT/HUMAN/lcc_human_n${i}.txt | grep -v 'a'
    wc -l ../OUT/HUMAN/lcc_human_n${i}.txt | awk '{print $1}'
done

echo "HUMAN_S"
for i in 1 3 5 8; do
    timeout 30s ./main/program ../data/lcc_human.igraph ../query/lcc_human_s${i}.igraph ../candidate_set/lcc_human_s${i}.cs > ../OUT/HUMAN/lcc_human_s${i}.txt
    tail -n1 ../OUT/HUMAN/lcc_human_s${i}.txt | grep -v 'a'
    wc -l ../OUT/HUMAN/lcc_human_s${i}.txt | awk '{print $1}'
done

######### YEAST

mkdir ../OUT/YEAST

echo "YEAST_N"
for i in 1 3 5 8; do
    timeout 30s ./main/program ../data/lcc_yeast.igraph ../query/lcc_yeast_n${i}.igraph ../candidate_set/lcc_yeast_n${i}.cs > ../OUT/YEAST/lcc_yeast_n${i}.txt
    tail -n1 ../OUT/YEAST/lcc_yeast_n${i}.txt | grep -v 'a'
    wc -l ../OUT/YEAST/lcc_yeast_n${i}.txt | awk '{print $1}'
done

echo "YEAST_S"
for i in 1 3 5 8; do
    timeout 30s ./main/program ../data/lcc_yeast.igraph ../query/lcc_yeast_s${i}.igraph ../candidate_set/lcc_yeast_s${i}.cs > ../OUT/YEAST/lcc_yeast_s${i}.txt
    tail -n1 ../OUT/YEAST/lcc_yeast_s${i}.txt | grep -v 'a'
    wc -l ../OUT/YEAST/lcc_yeast_s${i}.txt | awk '{print $1}'
done

