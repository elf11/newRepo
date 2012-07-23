import java.util.*;
import java.util.Map.Entry;

public class Ants {
	private int turn = 0;
	private int turns = 0;
	private int rows = 0;
	private int cols = 0;
	private int loadtime = 0;
	private int turntime = 0;
	private int viewradius2 = 0;
	private int attackradius2 = 0;
	private int spawnradius2 = 0;
	private long seed = 0;
	private Tile map[][];
	private Map<Tile, Integer> antList = new HashMap<Tile, Integer>();
	private HashSet<Tile> foodList = new HashSet<Tile>();
	private Set<Tile> deadList = new HashSet<Tile>();
	private HashSet<Tile> hills = new HashSet<Tile>();
	private HashSet<Tile> enemyHills = new HashSet<Tile>();
	//private Set<Ant> antInstances = new HashSet<Ant>();
	
	public int turn() {
		return this.turn;
	}

	public int turns() {
		return this.turns;
	}

	public int rows() {
		return this.rows;
	}

	public int cols() {
		return this.cols;
	}

	public int loadtime() {
		return this.loadtime;
	}

	public int turntime() {
		return this.turntime;
	}

	public int viewradius2() {
		return this.viewradius2;
	}

	public int attackradius2() {
		return this.attackradius2;
	}

	public int spawnradius2() {
		return this.spawnradius2;
	}

	public long seed() {
		return this.seed;
	}
	
	public Tile[][] map(){
		return map;
	}

	public boolean setup(List<String> data) {
		try {
			for (String line : data) {
			    String tokens[] = line.toLowerCase().split(" ");
			    if (tokens[0].equals("cols")) {
			    	this.cols = Integer.parseInt(tokens[1]);		    	
			    } else if (tokens[0].equals("rows")) {
			    	this.rows = Integer.parseInt(tokens[1]);
			    } else if (tokens[0].equals("turns")) {
			    	this.turns = Integer.parseInt(tokens[1]);
			    } else if (tokens[0].equals("loadtime")) {
			    	this.loadtime = Integer.parseInt(tokens[1]);
			    } else if (tokens[0].equals("turntime")) {
			    	this.turntime = Integer.parseInt(tokens[1]);
			    } else if (tokens[0].equals("viewradius2")) {
			    	this.viewradius2 = Integer.parseInt(tokens[1]);
			    } else if (tokens[0].equals("attackradius2")) {
			    	this.attackradius2 = Integer.parseInt(tokens[1]);
			    } else if (tokens[0].equals("spawnradius2")) {
			    	this.spawnradius2 = Integer.parseInt(tokens[1]);
			    } else if (tokens[0].equals("player_seed")) {
			    	this.seed = Long.parseLong(tokens[1]);
			    }
			}
			map = new Tile[ rows ][ cols ];
			for (int i = 0 ; i< rows; i++)
				for (int j = 0 ; j < cols; j++)
					map [i] [j] = new Tile(i,j);
			return true;
		} catch (Exception ex) {
			return false;
		}
	}
	
	private boolean update(List<String> data) {
		// clear ants and food
		for (Tile ant : this.antList.keySet()) {
			this.map[ant.row()][ant.col()].content(Ilk.LAND);
		}
		this.antList.clear();
		for (Tile food : this.foodList) {
			this.map[food.row()][food.col()].content(Ilk.LAND);
		}
		this.foodList.clear();
		
		for (Tile dead : this.deadList) {
			this.map[dead.row()][dead.col()].content(Ilk.LAND);
		}
		this.deadList.clear();
		// get new tile ilks
		for (String line : data) {
			String tokens[] = line.split(" ");
			if (tokens.length > 2) {
				int row = Integer.parseInt(tokens[1]);
				int col = Integer.parseInt(tokens[2]);
				if (tokens[0].equals("w")) {
			    	this.map[row][col].content( Ilk.WATER);
			    } else if (tokens[0].equals("a")) {
			    	int id = Integer.parseInt(tokens[3]);
			    	this.antList.put(map[row][col], id);
			    } else if (tokens[0].equals("f")) {
			    	this.map[row][col].content(Ilk.FOOD);
			    	this.foodList.add( map[row] [col]);
			    } else if (tokens[0].equals("d")) {
			    	this.map[row][col].content(Ilk.LAND);
			    	//this.deadList.add( map[row] [col]);
			    	map[row][col].resident(null);
			    } else if (tokens[0].equals("h")) { // am adaugat musuroaiele in lista hills
			    	if (this.turn == 1 && tokens[3].equals("0")){
			    		this.hills.add( map[row] [col]);
			    		map[row][col].content( Ilk.MY_HILL);
			    	}
			    	else if ( !tokens[3].equals("0")){
			    		this.enemyHills.add( map[row] [col]);
			    		map[row][col].content( Ilk.ENEMY_HILL);
			    	}
			    	
			    }
			}
		}
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				map[i][j].resident(null);
		for (Tile t: antList.keySet()){
			int id = antList.get(t);
			Ant ant = new Ant(id, t);
			map[t.row()][t.col()].resident(ant );
		}
			
		
		return true;
	}
	
	public void issueOrder(int row, int col, Aim direction) {
		System.out.println("o " + row + " " + col + " " + direction.symbol);
		System.out.flush();
	}

	public void issueOrder(Tile ant, Aim direction) {
		System.out.println("o " + ant.row() + " " + ant.col() + " " + direction.symbol);
		System.out.flush();
	}
	
	public void finishTurn() {
		System.out.println("go");
		System.out.flush();
		this.turn++;
	}
	
	//TO DO se poate folosi Ilk din Tile si se evita folosirea unui Map !!!!
	public HashSet<Tile> myAnts() {
		HashSet<Tile> myAnts = new HashSet<Tile>();
		for (Entry<Tile, Integer> ant : this.antList.entrySet()) {
			if (ant.getValue() == 0) {
				myAnts.add(ant.getKey());
			}
		}
		return myAnts;
	}
	
	public HashSet<Tile> enemyAnts() {
		HashSet<Tile> enemyAnts = new HashSet<Tile>();
		for (Entry<Tile, Integer> ant : this.antList.entrySet()) {
			if (ant.getValue() > 0) {
				enemyAnts.add(ant.getKey());
			}
		}
		return enemyAnts;
	}
	
	public Set<Tile> allAnts(){
		return antList.keySet();
	}
	
	public HashSet<Tile> food() {
		return this.foodList;
	}
	
	public HashSet<Tile> hills() {
		return this.hills;
	}
	/*
	public Set<Ant> antInstances() {
		return this.antInstances;
	}*/
	
	public HashSet<Tile> enemyHills(){
		return this.enemyHills;
	}
	
	public int distance (Tile t1, Tile t2) {
		int dRow = Math.abs(t1.row() - t2.row());
		int dCol = Math.abs(t1.col() - t2.col());

		dRow = Math.min(dRow, this.rows - dRow);
		dCol = Math.min(dCol, this.cols - dCol);
		
		return dRow * dRow + dCol * dCol;
	}
	
	// stabilirea directiei de parcurgere pentru deplasare de la t1 la t2 
	public List<Aim> directions (Tile t1, Tile t2) {
		List<Aim> directions = new ArrayList<Aim>();
		
		if (t1.row() < t2.row()) {
			if (t2.row() - t1.row() >= this.rows / 2) {
				directions.add(Aim.NORTH);
			} else {
				directions.add(Aim.SOUTH);
			}
		} else if (t1.row() > t2.row()) {
			if (t1.row() - t2.row() >= this.rows / 2) {
				directions.add(Aim.SOUTH);
			} else {
				directions.add(Aim.NORTH);
			}
		}

		if (t1.col() < t2.col()) {
			if (t2.col() - t1.col() >= this.cols / 2) {
				directions.add(Aim.WEST);
			} else {
				directions.add(Aim.EAST);
			}
		} else if (t1.col() > t2.col()) {
			if (t1.col() - t2.col() >= this.cols / 2) {
				directions.add(Aim.EAST);
			} else {
				directions.add(Aim.WEST);
			}
		}
		
		return directions;
	}
	
	public Ilk ilk(Tile location, Aim direction) {
		return this.tile(location, direction).content();
	}
	
	public Ilk ilk(Tile location) {
		return map[location.row()][location.col()].content();
	}
	
	public Tile tile(Tile location, Aim direction) {
		int nRow = (location.row() + direction.dRow) % this.rows;
		if (nRow < 0) {
			nRow += this.rows;
		}
		int nCol = (location.col() + direction.dCol) % this.cols;
		if (nCol < 0) {
			nCol += this.cols;
		}
		return map[nRow] [nCol];
	}

	public static void run(Bot bot, Strategy strategy) {
		Ants ants = new Ants();
		
		StringBuffer line = new StringBuffer();
		ArrayList<String> data = new ArrayList<String>();
		int c;	
		
		try {
		    while ((c = System.in.read()) >= 0) {
				switch (c) {
				case '\n':
				case '\r':
					if (line.length() > 0) {
						String full_line = line.toString();
						if (full_line.equals("ready")) {
							ants.setup(data);
							ants.finishTurn();
							data.clear();
							strategy.setAntWorld(ants);
						} else if (full_line.equals("go")) {
							ants.update(data);
							bot.do_turn(ants);
							ants.finishTurn();
							data.clear();
					    } else {
					    	if (line.length() > 0) {
					    		data.add(full_line);
					    	}
					    }
						line = new StringBuffer();
					}
				    break;
				default:
				    line.append((char)c);
				    break;
				}
		    }
		} catch (Exception e) {
			e.printStackTrace(System.err);
		}
		
	}
}
