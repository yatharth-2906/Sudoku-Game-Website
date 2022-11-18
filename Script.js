var arr = [[], [], [], [], [], [], [], [], []]

for (var i = 0; i < 9; i++) {
	for (var j = 0; j < 9; j++) {
		arr[i][j] = document.getElementById(i * 9 + j);

	}
}


var board = [[], [], [], [], [], [], [], [], []]

function FillBoard(board) {
	for (var i = 0; i < 9; i++) {
		for (var j = 0; j < 9; j++) {
			if (board[i][j] != 0) {
				arr[i][j].innerText = board[i][j]
			}

			else
				arr[i][j].innerText = ''
		}
	}
}

let GetPuzzle = document.getElementById('GetPuzzle')
let SolvePuzzle = document.getElementById('SolvePuzzle')

GetPuzzle.onclick = function () {
	var xhrRequest = new XMLHttpRequest()
	xhrRequest.onload = function () {
		var response = JSON.parse(xhrRequest.response)
		console.log(response)
		board = response.board
		FillBoard(board)
	}
	xhrRequest.open('get', 'https://sugoku.herokuapp.com/board?difficulty=hard')
    // API - LINK : https://github.com/bertoort/sugoku
	//we can change the difficulty of the puzzle the allowed values of difficulty are easy, medium, hard and random
	xhrRequest.send()
}

SolvePuzzle.onclick = () => {
	Sudoku_Solver(board, 9, 0, 0);
};

function Check_Validation(board, n, i, j, num)
{
    let row = 0, col = 0;

    // Column Check
    for(row = 0;  row < n; row++)
    {
        if(board[row][j] == num)
            return false;
    }

    // Row Check
    for(col = 0;  col < n; col++)
    {
        if(board[i][col] == num)
            return false;
    }

    // Sub-Matrix Check
    let sqn = Math.sqrt(n);
    row = i - (i%sqn);
    col = j - (j%sqn);
    for(i=0; i<sqn; i++)
    {
        for(j=0; j<sqn; j++)
        {
            if(board[i+row][j+col] == num)
                return false;
        }
    }

    return true;
}

function Sudoku_Solver(board, n, i, j)
{
    if(i == n)
    {
        FillBoard(board);
        return true;
    }

    else if(j == n)
    {
        return Sudoku_Solver(board,n,i+1,0);
    }

    else if (board[i][j] > 0)
        return Sudoku_Solver(board,n,i,j+1);
    
    for(let num = 1; num <= 9; num++)
    {
        if(Check_Validation(board,n,i,j,num) == true)
        {
            board[i][j] = num;
            let vara = Sudoku_Solver(board,n,i,j+1);
            if(vara == true)
            {
                return true;
            }
            else
            {
                board[i][j] = 0;
            }
        }
    }

    return false;
}