#include < iostream > 
using namespace std;
# include  "hw2.h"

Piece * Piece::board[9][OUT] = {
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL },
	{ NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL } };


int  main()	{
	//	place	16 pawns			
	for (int c = A; c <= H; ++c)
	{
		create("pawn", BLACK, (Column)c, 7);
		create("pawn", WHITE, (Column)c, 2);
	}
	//	white	pieces					
	create("rook", WHITE, A, 1);
	create("knight", WHITE, B, 1);
	create("bishop", WHITE, C, 1);
	create("queen", WHITE, D, 1);
	create("king", WHITE, E, 1);
	create("bishop", WHITE, F, 1);
	create("knight", WHITE, G, 1);
	create("rook", WHITE, H, 1);
	//  black  pieces											
	create("rook", BLACK, A, 8);
	create("knight", BLACK, B, 8);
	create("bishop", BLACK, C, 8);
	create("king", BLACK, D, 8);
	create("queen", BLACK, E, 8);
	create("bishop", BLACK, F, 8);
	create("knight", BLACK, G, 8);
	create("rook", BLACK, H, 8);
	//  white  starts											
	Color	turn = WHITE;
	Piece::drawboard();

	while (1)  {
		char  sc, ec;
		int	sr, er;
		cout << " Turn : " << coltoname[turn] << "\n";
		//	input start	pos	and	end  pos as  "D7	E5"
		cin >> ws >> sc >> sr;
		cin >> ws >> ec >> er;
		try	{
			Piece	*p;
			//	ask	the	piece on start position
			//	if	no piece exist	on pos EmptyCell
			cout << endl << nametoc(sc) << endl;
			p = Piece::getpiece(nametoc(sc), sr);

			// if piece with the wrong color leave iteration
			if (p->getcolor() != turn) {
				cout << " not  turn  of  that  player \n";
				continue;
			}
			// move the piece on start location
			p->move(nametoc(ec), er);
			Piece::drawboard();

			// switch turns					
			turn = (Color)(!(int)turn);
		}
		catch (Exception	& e)	{
			e.output();	// output exception message
		}
	}
}