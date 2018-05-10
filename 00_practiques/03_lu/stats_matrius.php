<?php
// Fitxer que serveix com a test per les matrius.

//echo "Benvingut al programa per testejar matrius.\nIndica la ruta a l'executable: ";
//$exec = trim(fgets(STDIN));
$exec = $argv[1];

$sums = [0, 0, 0, 0, 0, 0];
$min = [0, 0, 0, 0, 0, 0];

for ($i = 0; $i <= 99; ++$i) {
  $matriu = "M".str_pad($i, 2, 0, STR_PAD_LEFT).".DAT";
  $output = [];
  $return;
  exec($exec." MM/".$matriu." l", $output, $return);
  if ($return != 0) {
    die("Hi ha hagut un error desconegut amb la matriu #".$i." (error ".$return.").\n");
  }
  $norms = explode(" ", $output[0]);

  foreach ($norms as $j => $v) {
    if ($v > $min[$j]) $min[$j] = $v;
    $sums[$j] += $v;
  }
}

foreach ($sums as &$sum) {
  $sum /= 100;
}

echo "Aqui mostrem les mitjanes de cada norma:\n";
echo "PA - LU: Norma_1: ".$sums[0]."  Norma_inf: ".$sums[1]."\n";
echo "Ax - b:  Norma_1: ".$sums[2]."  Norma_inf: ".$sums[3]."\n";
echo "AA^-1-I: Norma_1: ".$sums[4]."  Norma_inf: ".$sums[5]."\n\n";

echo "Aqui mostrem el maxim que hem aconseguit de cada norma:\n";
echo "PA - LU: Norma_1: ".$min[0]."  Norma_inf: ".$min[1]."\n";
echo "Ax - b:  Norma_1: ".$min[2]."  Norma_inf: ".$min[3]."\n";
echo "AA^-1-I: Norma_1: ".$min[4]."  Norma_inf: ".$min[5]."\n";

