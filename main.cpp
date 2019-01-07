#include "common.h"

Options options;
SequenceDB seq_db;


////////////////////////////////////  MAIN /////////////////////////////////////
int main(int argc, const char *argv[])
{
	string db_in;
	string db_out;
	clock_t start, finish;
	start = clock();
	double totaltime;
	//float begin_time = current_time();
	//float end_time;

	// ***********************************    parse command line and open file
	if (argc < 7) {
		print_usage();
		return 0;
	}
	//if (options.SetOptions( argc, argv ) == 0) print_usage(argv[0]);
	//int argc = 11;
	//const char *argv[] = { "./dmsc","-i" ,"E:\\C++\\data\\v2qian2k.txt", "-o" ,"db97" ,"-c", "0.97","-T","10"};
	options.SetOptions(argc, argv);
	options.Validate();
	//print_usage();
	db_in = options.input;   //options的类成员
	db_out = options.output; //options的类成员

	InitNAA(MAX_UAA);
	options.NAAN = NAAN_array[options.NAA];
	seq_db.NAAN = NAAN_array[options.NAA];

	//printf( "%i  %i  %i\n", sizeof(NVector<IndexCount>), seq_db.NAAN, sizeof(NVector<IndexCount>) * seq_db.NAAN );

	seq_db.Read(db_in.c_str(), options);
	cout << "total seq: " << seq_db.sequences.size() << endl;
	seq_db.SortDivide(options);
	//seq_db.ComputeDistance(options);
	seq_db.DoClustering(options);

	printf("\rwriting clusters\n");
	
	seq_db.Write_seqDB_to_clusters(options);
	//seq_db.WriteClusters(db_in.c_str(), db_out.c_str(), options);

	// write a backup clstr file in case next step crashes
	//seq_db.WriteExtra1D(options);
	cout << "DMSC program completed !" << endl;
	//end_time = current_time();
	//printf( "Total CPU time %.2f\n", end_time - begin_time );
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	//cout<<"\n此程序运行时间为"<<totaltime<<"秒！"<<endl;
	//system("pause");
	//end_time = current_time();
	printf("CPU time: %.2f s\n", totaltime);
	//system("pause");
	return 0;
} // END int main
