#include "muscle.h"
#include "locallock.h"

void MPCFlat::ProfSeq(const MultiSequence &MSA1,
  const Sequence &seq2, string &Path)
	{
	Path.clear();
	uint SeqCount1 = MSA1.GetSeqCount();
	uint ColCount1 = MSA1.GetColCount();
	uint SeqLength2 = seq2.GetLength();

	uint SMI = 0;
	MultiSequence CombinedSeqs;
	for (uint SeqIndex = 0; SeqIndex < SeqCount1; ++SeqIndex)
		{
		const Sequence *seq = MSA1.GetSequence(SeqIndex);
		Sequence *seq2 = seq->CopyDeleteGaps();
		CombinedSeqs.AddSequence(seq2, false);

		Sequence *HackSeq = (Sequence *) seq;
		HackSeq->m_SMI = SMI++;
		}

	Sequence *seq2dg = seq2.CopyDeleteGaps();
	CombinedSeqs.AddSequence(seq2dg, false);

	Sequence *HackSeq = (Sequence *) &seq2;
	HackSeq->m_SMI = SMI++;

	InitSeqs(&CombinedSeqs);
	InitPairs();
	uint PairCount = SIZE(m_Pairs);
	asserta(PairCount > 0);
	AllocPairCount(PairCount);
	InitDistMx();
	unsigned ThreadCount = GetRequestedThreadCount();
	uint PairCounter = 0;
#pragma omp parallel for num_threads(ThreadCount)
	for (int SeqIndex1 = 0; SeqIndex1 < (int) SeqCount1; ++SeqIndex1)
		{
		Lock();
		ProgressStep(PairCounter++, SeqCount1, "Calc posteriors");
		Unlock();

		uint PairIndex = GetPairIndex(SeqIndex1, SeqCount1);
		CalcPosterior(PairIndex);
		}

	MultiSequence MSA2;
	MSA2.AddSequence(&seq2, false);

	float *Post = AllocPost(ColCount1, SeqLength2);
	BuildPost(MSA1, MSA2, Post);
	float *DPRows = AllocDPRows(ColCount1, SeqLength2);
	char *TB = AllocTB(ColCount1, SeqLength2);

	CalcAlnFlat(Post, ColCount1, SeqLength2, DPRows, TB, Path);
	myfree(Post);
	myfree(DPRows);
	myfree(TB);
	}

void cmd_profseq()
	{
	MultiSequence MSA1;
	MultiSequence Query;
	MSA1.LoadMFA(opt(profseq), false);
	Query.LoadMFA(opt(input2), true);
	bool IsNucleo = MSA1.GuessIsNucleo();
	bool IsNucleo2 = Query.GuessIsNucleo();
	asserta(IsNucleo2 == IsNucleo);
	if (IsNucleo)
		SetAlpha(ALPHA_Nucleo);
	else
		SetAlpha(ALPHA_Amino);

	uint PerturbSeed = 0;
	if (optset_perturb)
		PerturbSeed = opt(perturb);

	HMMParams HP;
	HP.FromDefaults(IsNucleo);
	if (PerturbSeed > 0)
		{
		ResetRand(PerturbSeed);
		HP.PerturbProbs(PerturbSeed);
		}
	HP.ToPairHMM();

	const uint QuerySeqCount = Query.GetSeqCount();
	for (uint QuerySeqIndex = 0; QuerySeqIndex < QuerySeqCount; ++QuerySeqIndex)
		{
		const Sequence *seq = Query.GetSequence(QuerySeqIndex);
		MPCFlat M;
		string Path;
		M.ProfSeq(MSA1, *seq, Path);
		Log("%s\n", Path.c_str());
		}
	}
 