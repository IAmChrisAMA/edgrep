int main(int argc, char *argv[]) {
	char *p1, *p2;
	// SIG_TYP oldintr;

	// oldquit = signal(SIGQUIT, SIG_IGN);
	// oldhup = signal(SIGHUP, SIG_IGN);
	// oldintr = signal(SIGINT, SIG_IGN);
	// if (signal(SIGTERM, SIG_IGN) == SIG_DFL)
	// 	signal(SIGTERM, quit);
	argv++;
	while (argc > 1 && **argv=='-') {
		switch((*argv)[1]) {

		case '\0':
			vflag = 0;
			break;

		case 'q':
			// signal(SIGQUIT, SIG_DFL);
			vflag = 1;
			break;

		case 'o':
			oflag = 1;
			break;
		}
		argv++;
		argc--;
	}
	if (oflag) {
		p1 = "/dev/stdout";
		p2 = savedfile;
		while (*p2++ = *p1++)
			;
	}
	if (argc>1) {
		p1 = *argv;
		p2 = savedfile;
		while (*p2++ = *p1++)
			if (p2 >= &savedfile[sizeof(savedfile)])
				p2--;
		globp = "r";
	}
	zero = (unsigned *)malloc(nlall*sizeof(unsigned));
	tfname = mktemp(tmpXXXXX);
	init();
	// if (oldintr!=SIG_IGN)
	// 	signal(SIGINT, onintr);
	// if (oldhup!=SIG_IGN)
	// 	signal(SIGHUP, onhup);
	setjmp(savej);
	commands();
	quit(0);
	return 0;
}

void commands(void) {
	unsigned int *a1;
	int c;
	int temp;
	char lastsep;

	for (;;) {
	if (pflag) {
		pflag = 0;
		addr1 = addr2 = dot;
		print();
	}
	c = '\n';
	for (addr1 = 0;;) {
		lastsep = c;
		a1 = address();
		c = getchr();
		if (c!=',' && c!=';')
			break;
		if (lastsep==',')
			error(Q);
		if (a1==0) {
			a1 = zero+1;
			if (a1>dol)
				a1--;
		}
		addr1 = a1;
		if (c==';')
			dot = a1;
	}
	if (lastsep!='\n' && a1==0)
		a1 = dol;
	if ((addr2=a1)==0) {
		given = 0;
		addr2 = dot;
	}
	else
		given = 1;
	if (addr1==0)
		addr1 = addr2;
	switch(c) {

	case 'f':         // Sets default filename to file.
		setnoaddr();
		filename(c);
		puts(savedfile);
		continue;

	case 'g':         // Search file
		global(1);
		continue;

	case 'n':         // Prints the addressed lines along with their number
		listn++;
		newline();
		print();
		continue;

	case '\n':        // Reads the input
		if (a1==0) {
			a1 = dot+1;
			addr2 = a1;
			addr1 = a1;
		}
		if (lastsep==';')
			addr1 = a1;
		print();
		continue;

	case 'l':         // Prints the addressed line unambigously.
		listf++;
	case 'p':         // Prints the addressed lines. If invoked from a terminal.
	case 'P':
		newline();
		print();
		continue;

	case 'Q':         // Quits ed UNCONDITIONALLY
		fchange = 0;
	case 'q':         // Quits ed
		setnoaddr();
		newline();
		quit(0);

	case 'r':         // Reads from file
		filename(c);
	caseread:
		if ((io = open(file, 0)) < 0) {
			lastc = '\n';
			error(file);
		}
		setwide();
		squeeze(0);
		ninbuf = 0;
		c = zero != dol;
		append(getfile, addr2);
		exfile();
		fchange = c;
		continue;

	case 'u':         // Undoes last command
		nonzero();
		newline();
		if ((*addr2&~01) != subnewa)
			error(Q);
		*addr2 = subolda;
		dot = addr2;
		continue;

	case 'v':         // Sets command-list tag
		global(0);
		continue;

	case EOF:         // EOF (Quits)
		return;

	}
	error(Q);
	}
}


//============================================================================================================//

// 	char *p1, *p2;
// 	argv++;
// 	while (argc > 1 && **argv=='-') {
// 		switch((*argv)[1]) {
//
// 		case '\0':
// 			vflag = 0;
// 			break;
//
// 		case 'q':
// 			vflag = 1;
// 			break;
//
// 		case 'o':
// 			oflag = 1;
// 			break;
// 		}
// 		argv++;
// 		argc--;
// 	}
// 	if (oflag) {
// 		p1 = "/dev/stdout";
// 		p2 = savedfile;
// 		while (*p2++ = *p1++)
// 			;
// 	}
// 	if (argc>1) {
// 		p1 = *argv;
// 		p2 = savedfile;
// 		while (*p2++ = *p1++)
// 			if (p2 >= &savedfile[sizeof(savedfile)])
// 				p2--;
// 		globp = "r";
// 	}
// 	zero = (unsigned *)malloc(nlall*sizeof(unsigned));
// 	tfname = mktemp(tmpXXXXX);
// 	init();
// 	setjmp(savej);
// 	commands();
// 	quit(0);
// 	return 0;
// }
//
// void commands(void) {
// 	unsigned int *a1;
// 	int c;
// 	int temp;
// 	char lastsep;
//
// 	for (;;) {
// 	if (pflag) {
// 		pflag = 0;
// 		addr1 = addr2 = dot;
// 		print();
// 	}
// 	c = '\n';
// 	for (addr1 = 0;;) {
// 		lastsep = c;
// 		a1 = address();
// 		c = getchr();
// 		if (c!=',' && c!=';')
// 			break;
// 		if (lastsep==',')
// 			error(Q);
// 		if (a1==0) {
// 			a1 = zero+1;
// 			if (a1>dol)
// 				a1--;
// 		}
// 		addr1 = a1;
// 		if (c==';')
// 			dot = a1;
// 	}
// 	if (lastsep!='\n' && a1==0)
// 		a1 = dol;
// 	if ((addr2=a1)==0) {
// 		given = 0;
// 		addr2 = dot;
// 	}
// 	else
// 		given = 1;
// 	if (addr1==0)
// 		addr1 = addr2;
// 	switch(c) {
//
// 	case 'g':         // Search file
// 		global(1);
// 		continue;
//
// 	case '\n':        // Reads the input
// 		if (a1==0) {
// 			a1 = dot+1;
// 			addr2 = a1;
// 			addr1 = a1;
// 		}
// 		if (lastsep==';')
// 			addr1 = a1;
// 		print();
// 		continue;
//
// 	case 'l':         // Prints the addressed line unambigously.
// 		listf++;
// 	case 'p':         // Prints the addressed lines. If invoked from a terminal.
// 	case 'P':
// 		newline();
// 		print();
// 		continue;
//
// 	case 'r':         // Reads from file
// 		filename(c);
// 	caseread:
// 		if ((io = open(file, 0)) < 0) {
// 			lastc = '\n';
// 			error(file);
// 		}
// 		setwide();
// 		squeeze(0);
// 		ninbuf = 0;
// 		c = zero != dol;
// 		append(getfile, addr2);
// 		exfile();
// 		fchange = c;
// 		continue;
//
// 	case EOF:         // EOF (Quits)
// 		return;
//
// 	}
// 	error(Q);
// 	}
// }
