void commands(void) {  unsigned int *a1;  int c, temp;  char lastsep;
  for (;;) {
    if (pflag) { pflag = 0;  addr1 = addr2 = dot;  print(); }  c = '\n';
    for (addr1 = 0;;) {
      lastsep = c;  a1 = address();  c = getchr();
      if (c != ',' && c != ';') { break; }  if (lastsep==',') { error(Q); }
      if (a1==0) {  a1 = zero+1;  if (a1 > dol) { a1--; }  }  addr1 = a1;  if (c == ';') { dot = a1; }
    }
    if (lastsep != '\n' && a1 == 0) { a1 = dol; }
    if ((addr2 = a1)==0) { given = 0;  addr2 = dot;  } else { given = 1; }
    if (addr1==0) { addr1 = addr2; }

    switch(c) {
    //case EOF:  return;
    //======================================================================== //
    case '\n':  if (a1 == 0) { a1 = dot + 1;  addr2 = a1;  addr1 = a1; }
                if (lastsep == ';') { addr1 = a1; }  print();
    // case 'e':  setnoaddr(); if (vflag && fchange) { fchange = 0;  error(Q); } filename(c);  init();
    //            addr2 = zero;  if ((io = open((const char*)file, 0)) < 0) { lastc = '\n';  error(file); }
    //            setwide();  squeeze(0);
    //            ninbuf = 0;
    //            append(getfile, addr2);  exfile();  fchange = c; continue;
    case 'g':  global(1);
    case 'p':  case 'P':  newline();  print();
    case 'Q':  fchange = 0;  case 'q':  setnoaddr();  newline();  quit(0);
    case 'z':  grepline();
    default:  // fallthrough
    caseGrepError:  greperror(c);
    }  error(Q);
}
