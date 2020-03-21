<?php
// Fitxer que serveix per fer prob2

$start = 1;

$exec = "./lu/program";

for ($i = $start; $i <= 100; ++$i) {
  $matriu = "H".$i.".DAT";
  $output = "";
  $return = 0;
  exec($exec." data/".$matriu." l", $output, $return);
  echo $output[0]." ".$output[1]." ".$output[2]."\n";
  if ($return == 42) {
    die("La matriu era singular!");
  } elseif ($return != 0) {
    die("Hi ha hagut un error desconegut (error ".$return.").\n");
  }
}

