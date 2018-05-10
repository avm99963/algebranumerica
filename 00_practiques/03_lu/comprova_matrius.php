<?php
// Fitxer que serveix com a test per les matrius.

echo "Benvingut al programa per testejar matrius.\nIndica per quina matriu vols comencar: ";
$start = (int)trim(fgets(STDIN));

echo "Ruta a l'executable: ";
$exec = trim(fgets(STDIN));

for ($i = $start; $i <= 100; ++$i) {
  $matriu = "M".str_pad($i, 2, 0, STR_PAD_LEFT).".DAT";
  echo str_repeat("=", 40)."\n  ".$matriu."\n".str_repeat("=", 40)."\n\n";
  
  $output;
  $return;
  exec($exec." MM/".$matriu." l", $output, $return);
  echo implode($output, "\n")."\n";
  if ($return == 42) {
    die("La matriu era singular!");
  } elseif ($return != 0) {
    die("Hi ha hagut un error desconegut (error ".$return.").\n");
  }
  echo str_repeat("-", 20)."\nPrem una tecla per continuar amb la seguent matriu...\n";
  fgets(STDIN);
}

echo "Felicitats, has provat amb totes les matrius!\n";
