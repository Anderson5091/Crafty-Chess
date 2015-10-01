int EvaluateDraws()
{
  register int square;
/*
 ----------------------------------------------------------
|                                                          |
|   if lots of material is left, it's not a draw.          |
|                                                          |
 ----------------------------------------------------------
*/
  if (TotalWhitePieces >= 5 || TotalBlackPieces >=5) return(0);
/*
 ----------------------------------------------------------
|                                                          |
|   if white has a bishop and pawn(s) then the pawn had    |
|   better not be only rook pawns, or else the bishop had  |
|   better be the right color, otherwise its a DRAW if the |
|   black king can block the pawn.                         |
|                                                          |
 ----------------------------------------------------------
*/
  if ((TotalWhitePieces == 3) && (TotalBlackPieces == 0) &&
      TotalWhitePawns && !And(WhitePawns,not_rook_pawns)) {
    if (And(WhiteBishops,dark_squares)) {
      if (And(file_mask[FILEH],WhitePawns)) return(0);
    }
    else if (And(file_mask[FILEA],WhitePawns)) return(0);

    square=LastOne(WhitePawns);
    if (Rank(BlackKingSQ) >= Rank(square))
      if (FileDistance(BlackKingSQ,square)<=1) return(1);
    return(0);
  }
/*
 ----------------------------------------------------------
|                                                          |
|   if black has a bishop and pawn(s) then the pawn had    |
|   better not be only rook pawns, or else the bishop had  |
|   better be the right color, otherwise its a DRAW if the |
|   white king can block the pawn.                         |
|                                                          |
 ----------------------------------------------------------
*/
  if ((TotalBlackPieces == 3) && (TotalWhitePieces == 0) &&
      TotalBlackPawns && !And(BlackPawns,not_rook_pawns)) {^¿
    if (And(BlackBishops,dark_squares)) {
      if (And(file_mask[FILEA],BlackPawns)) return(0);
    }
    else if (And(file_mask[FILEH],BlackPawns)) return(0);

    square=FirstOne(BlackPawns);
    if (Rank(WhiteKingSQ) <= Rank(square))
      if (FileDistance(WhiteKingSQ,square)<=1) return(1);
    return(0);
  }
/*
 ----------------------------------------------------------
|                                                          |
|   if both sides have pawns, the game is not a draw for   |
|   lack of material.  also, if one side has at least a    |
|   B+N, then it's not a drawn position.                   |
|                                                          |
 ----------------------------------------------------------
*/
  if (!TotalWhitePawns && !TotalBlackPawns &&
      TotalWhitePieces < 5 && TotalBlackPieces < 5) return(1);
  if (TotalWhitePawns == 0 && TotalWhitePieces < 5) return(-1);
  else if (TotalBlackPawns == 0 && TotalBlackPieces < 5) return(-2);
  return(0);
}
