<?php
// Fitxer que serveix per fer prob2

$start = 1;

$exec = "./lu/program";

for ($i = $start; $i <= 100; ++$i) {
  $matriu = "H".$i.".DAT";
  echo str_repeat("=", 40)."\n  ".$matriu."\n".str_repeat("=", 40)."\n\n";
  
  $output = "";
  $return = 0;
  exec($exec." data/".$matriu." l", $output, $return);
  echo implode($output, "\n")."\n";
  if ($return == 42) {
    die("La matriu era singular!");
  } elseif ($return != 0) {
    die("Hi ha hagut un error desconegut (error ".$return.").\n");
  }
  echo str_repeat("-", 20)."\nPrem enter per continuar amb la seguent matriu...\n";
  fgets(STDIN);
}

echo "Felicitats, has provat amb totes les matrius!\n";
