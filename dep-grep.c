//                    THE FIRST CRUSADE
//=============================================================//


// case 'a':         // Appends text to buffer
// 	add(0);
// 	continue;

// case 'c':         // Changes lines in buffer
// 	nonzero();
// 	newline();
// 	rdelete(addr1, addr2);
// 	append(gettty, addr1-1);
// 	continue;

// case 'd':         // Deletes the addressed lines from the buffer.
// 	nonzero();
// 	newline();
// 	rdelete(addr1, addr2);
// 	continue;

// case 'E':         // Edits file unconditionally.
// 	fchange = 0;
// 	c = 'e';
// case 'e':         // Edits file.
// 	setnoaddr();
// 	if (vflag && fchange) {
// 		fchange = 0;
// 		error(Q);
// 	}
// 	filename(c);
// 	init();
// 	addr2 = zero;
// 	// goto caseread; << Probably need but not goto

// case 'i':         // Inserts text
// 	add(-1);
// 	continue;

// case 'j':         // Joins the addressed lines.
// 	if (!given)
// 		addr2++;
// 	newline();
// 	join();
// 	continue;

// case 'k':         // Marks a line with a lower case letter
// 	nonzero();
// 	if ((c = getchr()) < 'a' || c > 'z')
// 		error(Q);
// 	newline();
// 	names[c-'a'] = *addr2 & ~01;
// 	anymarks |= 01;
// 	continue;

// case 'm':         // Moves lines in the buffer
// 	move(0);
// 	continue;

// case 's':         // Replaces last substition
// 	nonzero();
// 	substitute(globp!=0);
// 	continue;

// case 't':         // Copies the addressed lines to after the right-hand destination
// 	move(1);
// 	continue;

// case 'W':         // Appends to EOF
// 	wrapp++;
// case 'w':         // Writes to addressed lines to the standart input
// 	setwide();
// 	squeeze(dol>zero);
// 	if ((temp = getchr()) != 'q' && temp != 'Q') {
// 		peekc = temp;
// 		temp = 0;
// 	}
// 	filename(c);
// 	if(!wrapp ||
// 	  ((io = open(file,1)) == -1) ||
// 	  ((lseek(io, 0L, 2)) == -1))
// 		if ((io = creat(file, 0666)) < 0)
// 			error(file);
// 	wrapp = 0;
// 	if (dol > zero)
// 		putfile();
// 	exfile();
// 	if (addr1<=zero+1 && addr2==dol)
// 		fchange = 0;
// 	if (temp == 'Q')
// 		fchange = 0;
// 	if (temp)
// 		quit(0);
// 	continue;

// case '=':         // Prints the line number of the addressed line
// 	setwide();
// 	squeeze(0);
// 	newline();
// 	count = addr2 - zero;
// 	putd();
// 	putchr('\n');
// 	continue;

// case '!':         // Executes via sh
// 	callunix();
// 	continue;

// void join(void) {
// 	char *gp, *lp;
// 	unsigned int *a1;
//
// 	nonzero();
// 	gp = genbuf;
// 	for (a1=addr1; a1<=addr2; a1++) {
// 		lp = getline(*a1);
// 		while (*gp = *lp++)
// 			if (gp++ >= &genbuf[LBSIZE-2])
// 				error(Q);
// 	}
// 	lp = linebuf;
// 	gp = genbuf;
// 	while (*lp++ = *gp++)
// 		;
// 	*addr1 = putline();
// 	if (addr1<addr2)
// 		rdelete(addr1+1, addr2);
// 	dot = addr1;
// }

// void substitute(int inglob) {
// 	int *mp, nl;
// 	unsigned int *a1;
// 	int gsubf;
// 	int n;
//
// 	n = getnum();	/* OK even if n==0 */
// 	gsubf = compsub();
// 	for (a1 = addr1; a1 <= addr2; a1++) {
// 		if (execute(a1)){
// 			unsigned *ozero;
// 			int m = n;
// 			do {
// 				int span = loc2-loc1;
// 				if (--m <= 0) {
// 					dosub();
// 					if (!gsubf)
// 						break;
// 					if (span==0) {	/* null RE match */
// 						if (*loc2=='\0')
// 							break;
// 						loc2++;
// 					}
// 				}
// 			} while (execute((unsigned *)0));
// 			if (m <= 0) {
// 				inglob |= 01;
// 				subnewa = putline();
// 				*a1 &= ~01;
// 				if (anymarks) {
// 					for (mp = names; mp < &names[26]; mp++)
// 						if (*mp == *a1)
// 							*mp = subnewa;
// 				}
// 				subolda = *a1;
// 				*a1 = subnewa;
// 				ozero = zero;
// 				nl = append(getsub, a1);
// 				nl += zero-ozero;
// 				a1 += nl;
// 				addr2 += nl;
// 			}
// 		}
// 	}
// 	if (inglob==0)
// 		error(Q);
// }

// int compsub(void) {
// 	int seof, c;
// 	char *p;
//
// 	if ((seof = getchr()) == '\n' || seof == ' ')
// 		error(Q);
// 	compile(seof);
// 	p = rhsbuf;
// 	for (;;) {
// 		c = getchr();
// 		if (c=='\\')
// 			c = getchr() | 0200;
// 		if (c=='\n') {
// 			if (globp && globp[0])	/* last '\n' does not count */
// 				c |= 0200;
// 			else {
// 				peekc = c;
// 				pflag++;
// 				break;
// 			}
// 		}
// 		if (c==seof)
// 			break;
// 		*p++ = c;
// 		if (p >= &rhsbuf[LBSIZE/2])
// 			error(Q);
// 	}
// 	*p++ = 0;
// 	if ((peekc = getchr()) == 'g') {
// 		peekc = 0;
// 		newline();
// 		return(1);
// 	}
// 	newline();
// 	return(0);
// }

// void rdelete(unsigned int *ad1, unsigned int *ad2) {
// 	unsigned int *a1, *a2, *a3;
//
// 	a1 = ad1;
// 	a2 = ad2+1;
// 	a3 = dol;
// 	dol -= a2 - a1;
// 	do {
// 		*a1++ = *a2++;
// 	} while (a2 <= a3);
// 	a1 = ad1;
// 	if (a1 > dol)
// 		a1 = dol;
// 	dot = a1;
// 	fchange = 1;
// }

// void add(int i) {
// 	if (i && (given || dol>zero)) {
// 		addr1--;
// 		addr2--;
// 	}
// 	squeeze(0);
// 	newline();
// 	append(gettty, addr2);
// }

// void callunix(void) {
// 	SIG_TYP savint;
// 	int pid, rpid;
// 	int retcode;
//
// 	setnoaddr();
// 	if ((pid = fork()) == 0) {
// 		signal(SIGHUP, oldhup);
// 		signal(SIGQUIT, oldquit);
// 		execl("/bin/sh", "sh", "-t", 0);
// 		exit(0100);
// 	}
// 	savint = signal(SIGINT, SIG_IGN);
// 	while ((rpid = wait(&retcode)) != pid && rpid != -1)
// 		;
// 	signal(SIGINT, savint);
// 	if (vflag) {
// 		puts("!");
// 	}
// }

//                    THE SECOND CRUSADE
//=============================================================//


// int getsub(void) {
// 	char *p1, *p2;
//
// 	p1 = linebuf;
// 	if ((p2 = linebp) == 0)
// 		return(EOF);
// 	while (*p1++ = *p2++)
// 		;
// 	linebp = 0;
// 	return(0);
// }

// void dosub(void) {
// 	char *lp, *sp, *rp;
// 	int c;
//
// 	lp = linebuf;
// 	sp = genbuf;
// 	rp = rhsbuf;
// 	while (lp < loc1)
// 		*sp++ = *lp++;
// 	while (c = *rp++&0377) {
// 		if (c=='&') {
// 			sp = place(sp, loc1, loc2);
// 			continue;
// 		} else if (c&0200 && (c &= 0177) >='1' && c < nbra+'1') {
// 			sp = place(sp, braslist[c-'1'], braelist[c-'1']);
// 			continue;
// 		}
// 		*sp++ = c&0177;
// 		if (sp >= &genbuf[LBSIZE])
// 			error(Q);
// 	}
// 	lp = loc2;
// 	loc2 = sp - genbuf + linebuf;
// 	while (*sp++ = *lp++)
// 		if (sp >= &genbuf[LBSIZE])
// 			error(Q);
// 	lp = linebuf;
// 	sp = genbuf;
// 	while (*lp++ = *sp++)
// 		;
// }

// char *
// place(char *sp, char *l1, char *l2) {
// 	while (l1 < l2) {
// 		*sp++ = *l1++;
// 		if (sp >= &genbuf[LBSIZE])
// 			error(Q);
// 	}
// 	return(sp);
// }

// void move(int cflag) {
// 	unsigned int *adt, *ad1, *ad2;
//
// 	nonzero();
// 	if ((adt = address())==0)	/* address() guarantees addr is in range */
// 		error(Q);
// 	newline();
// 	if (cflag) {
// 		unsigned int *ozero;
// 		int delta;
//
// 		ad1 = dol;
// 		ozero = zero;
// 		append(getcopy, ad1++);
// 		ad2 = dol;
// 		delta = zero - ozero;
// 		ad1 += delta;
// 		adt += delta;
// 	} else {
// 		ad2 = addr2;
// 		for (ad1 = addr1; ad1 <= ad2;)
// 			*ad1++ &= ~01;
// 		ad1 = addr1;
// 	}
// 	ad2++;
// 	if (adt<ad1) {
// 		dot = adt + (ad2-ad1);
// 		if ((++adt)==ad1)
// 			return;
// 		reverse(adt, ad1);
// 		reverse(ad1, ad2);
// 		reverse(adt, ad2);
// 	} else if (adt >= ad2) {
// 		dot = adt++;
// 		reverse(ad1, ad2);
// 		reverse(ad2, adt);
// 		reverse(ad1, adt);
// 	} else
// 		error(Q);
// 	fchange = 1;
// }

// void reverse(unsigned int *a1, unsigned int *a2) {
// 	int t;
//
// 	for (;;) {
// 		t = *--a2;
// 		if (a2 <= a1)
// 			return;
// 		*a2 = *a1;
// 		*a1++ = t;
// 	}
// }

// int getcopy(void) {
// 	if (addr1 > addr2)
// 		return(EOF);
// 	getline(*addr1++);
// 	return(0);
// }

// case 'Q':         // Quits ed UNCONDITIONALLY
// 	fchange = 0;
// case 'q':         // Quits ed
// 	setnoaddr();
// 	newline();
// 	quit(0);

// case 'n':         // Prints the addressed lines along with their number
// 	listn++;
// 	newline();
// 	print();
// 	continue;

// void onintr(int n) {
// 	signal(SIGINT, onintr);
// 	putchr('\n');
// 	lastc = '\n';
// 	error(Q);
// }

void onhup(int n) {
	// signal(SIGINT, SIG_IGN);
	// signal(SIGHUP, SIG_IGN);
	if (dol > zero) {
		addr1 = zero+1;
		addr2 = dol;
		io = creat("ed.hup", 0600);
		if (io > 0)
			putfile();
	}
	fchange = 0;
	quit(0);
}

// int gettty(void) {
// 	int rc;
//
// 	if (rc = gety())
// 		return(rc);
// 	if (linebuf[0]=='.' && linebuf[1]==0)
// 		return(EOF);
// 	return(0);
// }

// int gety(void) {
// 	int c;
// 	char *gf;
// 	char *p;
//
// 	p = linebuf;
// 	gf = globp;
// 	while ((c = getchr()) != '\n') {
// 		if (c==EOF) {
// 			if (gf)
// 				peekc = c;
// 			return(c);
// 		}
// 		if ((c &= 0177) == 0)
// 			continue;
// 		*p++ = c;
// 		if (p >= &linebuf[LBSIZE-2])
// 			error(Q);
// 	}
//
// 	*p++ = 0;
// 	return(0);
// }

// void setwide(void) {
// 	if (!given) {
// 		addr1 = zero + (dol>zero);
// 		addr2 = dol;
// 	}
// }

// void setnoaddr(void) {
// 	if (given)
// 		error(Q);
// }

// void nonzero(void) {
// 	squeeze(1);
// }

// void squeeze(int i) {
// 	if (addr1<zero+i || addr2>dol || addr1>addr2)
// 		error(Q);
// }

// void newline(void) {
// 	int c;
//
// 	if ((c = getchr()) == '\n' || c == EOF)
// 		return;
// 	if (c=='p' || c=='l' || c=='n') {
// 		pflag++;
// 		if (c=='l')
// 			listf++;
// 		else if (c=='n')
// 			listn++;
// 		if ((c=getchr())=='\n')
// 			return;
// 	}
// 	error(Q);
// }
