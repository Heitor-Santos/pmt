algos=("aho-corasick")
patterns=("1" "1" "1" "1" "1" "1" "1" "1" "1" "1")
for algo in ${algos[@]}; do   
     echo $algo
     cont=10
     for pat in ${patterns[@]}; do
          echo PMT > "testes_exact_mult/teste-$algo-$cont-dna.txt"
          { time (../bin/pmt -c -p "patterns_$cont.txt" -a "$algo" tests_text_files/dna.txt > dummy.txt) ; } 2>> "testes_exact_mult/teste-$algo-$cont-dna.txt"
          echo "   " >> "testes_exact_mult/teste-$algo-$cont-dna.txt"
          echo GREP >> "testes_exact_mult/teste-$algo-$cont-dna.txt"
          { time (grep -c -f "patterns_$cont.txt" tests_text_files/dna.txt > dummy2.txt) ; } 2>> "testes_exact_mult/teste-$algo-$cont-dna.txt"


          # echo PMT > "testes_exact/teste-$algo-$cont-english.txt"
          # time ../bin/pmt -a "$algo" "$pat" tests_text_files/english.txt >> "testes_exact/teste-$algo-$cont-english.txt"
          # echo "   " >> "testes_exact/teste-$algo-$cont-english.txt"
          # echo GREP >> "testes_exact/teste-$algo-$cont-english.txt"
          # time grep "$pat" tests_text_files/english.txt >> "testes_exact/teste-$algo-$cont-english.txt"
          cont=$(($cont + 10))

     done
done