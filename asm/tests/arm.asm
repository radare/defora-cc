/* $Id$ */
.text
	adc	%r3, %r4, %r5
	adceq	%r3, %r4, %r5
	adcne	%r3, %r4, %r5
	adccs	%r3, %r4, %r5
	adccc	%r3, %r4, %r5
	adcmi	%r3, %r4, %r5
	adcpl	%r3, %r4, %r5
	adcvs	%r3, %r4, %r5
	adcvc	%r3, %r4, %r5
	adchi	%r3, %r4, %r5
	adcls	%r3, %r4, %r5
	adcge	%r3, %r4, %r5
	adclt	%r3, %r4, %r5
	adcgt	%r3, %r4, %r5
	adcle	%r3, %r4, %r5
	adcal	%r3, %r4, %r5
	adc	%r4, %r5, $0x0
	adceq	%r4, %r5, $0x1
	adcne	%r4, %r5, $0x2
	adccc	%r4, %r5, $0x3
	adcpl	%r4, %r5, $0x4
	adcvs	%r4, %r5, $0x5
	adcvc	%r4, %r5, $0x6
	adchi	%r4, %r5, $0x7
	adcls	%r4, %r5, $0x8
	adcge	%r4, %r5, $0x9
	adclt	%r4, %r5, $0xa
	adcgt	%r4, %r5, $0xb
	adcle	%r4, %r5, $0xc
	adcal	%r4, %r5, $0xd
	adcs	%r3, %r4, %r5
	adceqs	%r3, %r4, %r5
	adcs	%r3, %r4, $0x0
	adceqs	%r3, %r4, $0x1
	add	%r3, %r4, %r5
	addeq	%r3, %r4, %r5
	add	%r3, %r4, $0x0
	addeq	%r3, %r4, $0x1
	adds	%r3, %r4, %r5
	addeqs	%r3, %r4, %r5
	adds	%r3, %r4, $0x0
	addeqs	%r3, %r4, $0x1
	and	%r3, %r4, %r5
	andeq	%r3, %r4, %r5
	and	%r3, %r4, $0x0
	andeq	%r3, %r4, $0x1
	ands	%r3, %r4, %r5
	andeqs	%r3, %r4, %r5
	ands	%r3, %r4, $0x0
	andeqs	%r3, %r4, $0x1
	b	$0xa0
	beq	$0xa0
	bic	%r3, %r4, %r5
	biceq	%r3, %r4, %r5
	bic	%r3, %r4, $0x0
	biceq	%r3, %r4, $0x1
	bics	%r3, %r4, %r5
	biceqs	%r3, %r4, %r5
	bics	%r3, %r4, $0x0
	biceqs	%r3, %r4, $0x1
	bl	$0xa0
	bleq	$0xa0
	bx	%r1
	bxeq	%r2
	cdp	$0x1, $0xf, %r3
	cdpeq	$0x2, $0xe, %r4
	cmn	%r5, %r4
	cmneq	%r5, %r4
	cmn	%r5, $0x1
	cmneq	%r5, $0x2
	cmns	%r5, %r4
	cmneqs	%r5, %r4
	cmns	%r5, $0x1
	cmneqs	%r5, $0x2
	cmp	%r5, %r4
	cmpeq	%r5, %r4
	cmp	%r5, $0x1
	cmpeq	%r5, $0x2
	cmps	%r5, %r4
	cmpeqs	%r5, %r4
	cmps	%r5, $0x1
	cmpeqs	%r5, $0x2
	eor	%r3, %r4, %r5
	eoreq	%r3, %r4, %r5
	eor	%r3, %r4, $0x0
	eoreq	%r3, %r4, $0x1
	eors	%r3, %r4, %r5
	eoreqs	%r3, %r4, %r5
	eors	%r3, %r4, $0x0
	eoreqs	%r3, %r4, $0x1
	ldc	$0x1, %r2, $0x42
	ldceq	$0x2, %r1, $0x42
	ldm	%r2, $0x4442
	ldmeq	%r1, $0x4341
	ldr	%r4, [%r3], %r2
	ldreq	%r4, [%r3], %r2
	ldrb	%r4, [%r3], %r2
	ldreqb	%r4, [%r3], %r2
	mcr	$0x1, $0x4, %r3
	mcreq	$0x2, $0x3, %r1
	mla	%r3, %r1, %r2
	mlaeq	%r3, %r1, %r2
	mlas	%r3, %r1, %r2
	mlaeqs	%r3, %r1, %r2
	mov	%r4, %r0
	moveq	%r5, %r1
	mov	%r6, $0x1
	moveq	%r7, $0x2
	movs	%r8, %r4
	moveqs	%r9, %r5
	movs	%r10, $0x3
	moveqs	%r11, $0x4
	mrc	$0x1, $0x4, %r3
	mrceq	$0x2, $0x3, %r1
	mrs	%r0, %cpsr
	mrseq	%r1, %cpsr
	mrs	%r2, %spsr
	mrseq	%r3, %spsr
	msr	%cpsr, %r4
	msreq	%cpsr, %r5
	msr	%spsr, %r6
	msreq	%spsr, %r7
	mul	%r3, %r1, %r2
	muleq	%r3, %r1, %r2
	muls	%r3, %r1, %r2
	muleqs	%r3, %r1, %r2
	mvn	%r5, %r4
	mvneq	%r5, %r4
	mvn	%r5, $0x1
	mvneq	%r5, $0x2
	mvns	%r5, %r4
	mvneqs	%r5, %r4
	mvns	%r5, $0x3
	mvneqs	%r5, $0x4
	nop
	orr	%r3, %r4, %r5
	orreq	%r3, %r4, %r5
	orr	%r3, %r4, $0x0
	orreq	%r3, %r4, $0x1
	orrs	%r3, %r4, %r5
	orreqs	%r3, %r4, %r5
	orrs	%r3, %r4, $0x0
	orreqs	%r3, %r4, $0x1
	rsb	%r3, %r4, %r5
	rsbeq	%r3, %r4, %r5
	rsb	%r3, %r4, $0x0
	rsbeq	%r3, %r4, $0x1
	rsbs	%r3, %r4, %r5
	rsbeqs	%r3, %r4, %r5
	rsbs	%r3, %r4, $0x0
	rsbeqs	%r3, %r4, $0x1
	rsc	%r3, %r4, %r5
	rsceq	%r3, %r4, %r5
	rsc	%r3, %r4, $0x0
	rsceq	%r3, %r4, $0x1
	rscs	%r3, %r4, %r5
	rsceqs	%r3, %r4, %r5
	rscs	%r3, %r4, $0x0
	rsceqs	%r3, %r4, $0x1
	sbc	%r3, %r4, %r5
	sbceq	%r3, %r4, %r5
	sbc	%r3, %r4, $0x0
	sbceq	%r3, %r4, $0x1
	sbcs	%r3, %r4, %r5
	sbceqs	%r3, %r4, %r5
	sbcs	%r3, %r4, $0x0
	sbceqs	%r3, %r4, $0x1
	stc	$0x1, %r2, $0x42
	stceq	$0x2, %r1, $0x42
	stm	%r2, $0x4442
	stmeq	%r1, $0x4341
	str	%r7, [%r5], %r6
	streq	%r7, [%r5], %r6
	strb	%r7, [%r5], %r6
	streqb	%r7, [%r5], %r6
	sub	%r3, %r4, %r5
	subeq	%r3, %r4, %r5
	sub	%r3, %r4, $0x0
	subeq	%r3, %r4, $0x1
	subs	%r3, %r4, %r5
	subeqs	%r3, %r4, %r5
	subs	%r3, %r4, $0x0
	subeqs	%r3, %r4, $0x1
	swi	$0x42
	swine	$0x43
	swp	%r5, %r4, [%r3]
	swpeq	%r5, %r4, [%r3]
	swpb	%r5, %r4, [%r3]
	swpeqb	%r5, %r4, [%r3]
	teq	%r5, %r4
	teqeq	%r5, %r4
	teq	%r5, $0x1
	teqeq	%r5, $0x2
	teqs	%r5, %r4
	teqeqs	%r5, %r4
	teqs	%r5, $0x1
	teqeqs	%r5, $0x2
	tst	%r5, %r4
	tsteq	%r5, %r4
	tst	%r5, $0x1
	tsteq	%r5, $0x2
	tsts	%r5, %r4
	tsteqs	%r5, %r4
	tsts	%r5, $0x1
	tsteqs	%r5, $0x2
