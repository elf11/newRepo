import java.util.*;

class Logger{
	public static void log(int cod, String mes){
		//if (true)return;
		if (cod == 0){
			MyBot.file.println();
			return;
		}
		MyBot.file.printf("%3d : ", cod);
		MyBot.file.println(mes);
		MyBot.file.flush();
	}
}

class Coord {
	int x,y;
	public Coord (int xx, int yy){
		x = xx;
		y = yy;
	}
	public String toString(){
		return x+ " " + y;
	}
	public int hashCode(){
		return x * 1000 + y;
	}
}

class Area{
	int radius,
		enemyAnts,
		ants,
		nearEnemy,
		nearAnt,
		dangerZone,
		safeZone;
	public Area(){
		radius = ants = enemyAnts = 0;
		nearEnemy = nearAnt = dangerZone = safeZone = -1;
	}
}


public class Strategy{
	
	private static final Strategy instance = new Strategy();
	private static List<Aim> directions;
	private static Ants antWorld;

	public static Random rnd;
	private int rows;
	private int cols;
	private int[] stats;
	private Tile[][] map;
	private boolean AGGRESSIVE;
	private HashSet<Tile> 	myAnts;
	private Set	   <Tile> 	allAnts;
	private HashSet<Tile> 	hills;
	private HashSet<Tile> 	enemies;
	private HashSet<Tile> 	food;
	private HashSet<Tile> 	enemyHills;
	private HashSet<Coord> 	relativeVisible;
	private HashSet<Coord> 	relativeHillArea;
	private HashSet<Coord> 	relativeAtackArea;
	private HashSet<Tile>  	periferic;
	private long startTime;
	int sum, len, turn;
	
	
	private Strategy() { 
		directions = new ArrayList<Aim>(EnumSet.allOf(Aim.class));
	}
	
	public static Ants getAnts() { return antWorld; }
	
	public static List<Aim> getDirections() { return directions; }
	
	public static Strategy getInstance() { return instance;}
	
	public void setAntWorld( Ants ants ) {
		antWorld = ants; 
		init();
	}
	
	private void init(){
		final int MAX = 10;
		sum = 0;
		len = 10;
		rows = antWorld.rows();
		cols = antWorld.cols();
		stats = new int[antWorld.turns() + 2];
		map = antWorld.map();
		rnd = new Random(antWorld.seed());
		periferic = new HashSet<Tile>();
		relativeAtackArea = new HashSet<Coord>();
		relativeHillArea = new HashSet<Coord>();
		relativeVisible = new HashSet<Coord>();
		AGGRESSIVE = false;
		resetMap();
		
		for (int i = -MAX; i <= MAX; i++)
			for (int j = -MAX; j <= MAX; j++){
				if (i * i + j * j <= antWorld.viewradius2())
					relativeVisible.add(new Coord(i, j));
				if (i * i + j * j <= antWorld.attackradius2())
					relativeAtackArea.add(new Coord(i, j));
				if (i * i + j * j == 4 || i * i + j * j == 5)
					relativeHillArea.add(new Coord(i, j));
			}
		
	}
	
	public void turnInit(){
		turn 	= antWorld.turn();
		myAnts 	= antWorld.myAnts();
		allAnts = antWorld.allAnts();
		hills 	= antWorld.hills();
    	enemies	= antWorld.enemyAnts();
    	food 	= antWorld.food();
    	enemyHills = antWorld.enemyHills();
		stats[turn] = myAnts.size();
		sum += stats[turn];
		if (turn > len)
			sum -= stats[turn - len];
		
	}
	
	public void setTurnStartTime(long t) {
        startTime = t;
	}

	private int timeLeft() {
	        return antWorld.turntime() - (int)(System.currentTimeMillis() - startTime);
	}
	
	private Tile getTileByCoord(Tile t, Coord coord){
		int r = (t.row() + coord.x) % rows;
		int c = (t.col() + coord.y) % cols;
		r = (r < 0)? r + rows : r;
		c = (c < 0)? c + cols : c;
		return map[r][c];
	}
	
	private double compareScent(Tile t1, Tile t2){
		if (t1.scent() > t2.scent())
			return 1;
		else if (t1.scent() < t2.scent())
				return -1;
			 else return t1.seed() - t2.seed();
	}
	
	public void resetMap() {
		periferic.clear();
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++) {
				map[i][j].scent(0);
				map[i][j].seed(rnd.nextDouble());
			}
	}
	
	private boolean pozitive() {
		return (sum / len) < myAnts.size();
	}
	
	private HashSet<Tile> getVisible(Tile t) {
		HashSet<Tile> visible = new HashSet<Tile>();
		for (Coord c: relativeVisible)
			visible.add( getTileByCoord(t, c));
		return visible;
	}
	
	public void markVisible(){
		
		HashSet<Tile> visible;
		for (Tile t: myAnts){
			visible = getVisible( t );
			for (Tile x: visible)
				if (x.lastVisible() != turn) {
					x.lastVisible( turn );
					x.lastEmpty( turn );
				}
		}
		// celulele periferice
		
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				if (map[i][j].isPassable()) {
					Tile t;
					for (Aim d: directions) {
						t = antWorld.tile(map[i][j], d);
						if (t.lastVisible() == 0) periferic.add(t);
					}
				}
				
		Tile t = myAnts.iterator().next();
		HashSet<Tile> tmp = rangeTiles(t, relativeAtackArea);
		//Logger.log(100 + turn, tmp.size()+"");
		//for (Tile x:  tmp)
		//		Logger.log(100 + turn, x.toString());
	}
	
	public Area extendArea(HashSet<Tile> margins, double score, int antNr) {
		HashMap<Tile, Integer> areaTiles = new HashMap<Tile, Integer>();
		HashMap<Tile, Integer> busyTiles = new HashMap<Tile, Integer>();
		Area area = new Area();
		
		while (!margins.isEmpty()) {
			HashSet<Tile> newMargins = new HashSet<Tile>();
			area.radius++;
			
			for (Tile t: margins) {			// parcurg toate celulele marginale curente
				if (!areaTiles.containsKey(t)) {
					areaTiles.put(t, 0); 		// adaug celula la aria interogata
					if (t.resident() != null)
						if (t.resident().id() == 0) {
							area.ants++;
							area.nearAnt = (area.nearAnt < 0) ? area.radius : area.nearAnt;
						}
						else {
							area.enemyAnts++;
							area.nearEnemy = (area.nearEnemy < 0) ? area.radius : area.nearEnemy;
						}
				}
			}
			
			if (area.ants >= antNr && area.radius >= 2) break;
			
			// update la zonele de safety / danger
			area.safeZone = (area.safeZone < 0 && area.ants > area.enemyAnts) ? 
							 area.radius : area.safeZone;
			area.dangerZone = (area.dangerZone < 0 && area.ants > 0
							&& area.enemyAnts >= area.ants) ? area.radius : area.dangerZone;
					
			//extindem cu o celula raza daca este necesar
			for (Tile t: margins) {
				if (areaTiles.get(t) == 0) {
					areaTiles.put(t, 1);
					t.addscent( score / (area.radius * area.radius) );
				}
				//initializam celula cu numarul de ture in care a existat rezident
				if (t.resident() != null && t.resident().id() == 0 &&
					!busyTiles.containsKey(t)){
					busyTiles.put(t, ( t.lastVisible() == antWorld.turn() ) ? 
									  antWorld.turn() - t.lastEmpty() : 0);
					
				}
				int val;
				if (!busyTiles.containsKey(t)) busyTiles.put(t, 0);
				if ( (val = busyTiles.get(t)) > 1){	//nu extind marginea
					newMargins.add(t);
				}
				else{ //extind
					for (Aim d: directions) {
						Tile x = antWorld.tile(t, d);
						if (x.content() != Ilk.WATER && x.lastVisible() > 0 &&
							!areaTiles.containsKey(x)) {
							newMargins.add(x);
							busyTiles.put(x, 0);
						}
					}
				}
				busyTiles.put(t, val - 1);
			}
			margins = newMargins;
		}
		return area;
	}
	
	private HashSet<Tile> rangeTiles(Tile t, HashSet<Coord> coords){
		HashSet<Tile> visible = new HashSet<Tile>();
		for (Coord c: coords){
			Tile x = getTileByCoord(t, c);
			if (x.isPassable())
				visible.add(x);
		}
		return visible;
	}
	
	private HashSet<Tile> rangeBorder(Tile t, HashSet<Coord> coords){
		HashSet<Tile> visible = rangeTiles(t, coords);
		for (Aim d: directions){
			Tile x = antWorld.tile(t, d);
			if (x.isPassable())
				visible.addAll(rangeTiles(x, coords));
		}
		return visible;
	}
	
	private int enemyNr(Tile t, int player){
		HashSet<Tile> attackable;
		HashSet<Tile> border;
		HashSet<Tile> enemies = new HashSet<Tile>();
		HashSet<Tile> enemyRange;
		HashSet<Tile> toRemove = new HashSet<Tile>();
		HashSet<Coord> position = new HashSet<Coord>(Arrays.asList(new Coord(0,0)));
		int rangeEnemies = 0;
		boolean found = false;
		
		// celulele din raza de atac si zona periferica
		attackable = rangeTiles(t, relativeAtackArea);
		border = rangeBorder(t, relativeAtackArea);
		border.removeAll(attackable);
		
		// inamicii din zona de vizibilitate
		for (Tile x: attackable)
			if ( x.resident() != null && x.resident().id() != player)
				rangeEnemies++;
		
		// inamicii din zonele periferice
		for (Tile x: border)
			if ( x.resident() != null && x.resident().id() != player){
				enemies.add(x);
				found = true;
			}
		
		if (!found) return rangeEnemies;
		
		while (found && !enemies.isEmpty()){
			toRemove.clear();
			found = false;
			for (Tile x: enemies){
				enemyRange = rangeBorder(x, position);
				enemyRange.retainAll(attackable);
				if (enemyRange.size() == 1){
					found = true;
					rangeEnemies++;
					toRemove.add(x);
					attackable.removeAll(enemyRange);
				}
			}
			enemies.removeAll(toRemove);
		}
		
		for (Tile x: enemies){
			enemyRange = rangeBorder(x, position);
			enemyRange.retainAll(attackable);
			if (!enemyRange.isEmpty())
				rangeEnemies++;
		}
		return rangeEnemies;
	}
	
	private void calculateRisk(){
		int MAXplayers = 8;
		int SURVIVE = 0, ONE_ONE = 1, OWNED = 2;
		double[] scent = new double[] {0.3, -0.5, -1}; //Survive, One on one, Owned
		HashSet<Tile> combat = new HashSet<Tile>();
		HashSet<Tile> attackable;
		HashMap<Tile, Integer>[] tmp = new HashMap[MAXplayers];
		HashMap<Tile, Integer>[] bestEnemy = new HashMap[MAXplayers];
		HashMap<Tile, Integer>[] result = new HashMap[MAXplayers];
		HashSet<Coord> position = new HashSet<Coord>(Arrays.asList(new Coord(0, 0)));
		
		for (int i = 0; i < MAXplayers; i++){
			tmp[i] 		= new HashMap<Tile, Integer>();
			bestEnemy[i] = new HashMap<Tile, Integer>();
			result[i] 	= new HashMap<Tile, Integer>();
		}
		
		for (Tile ant: allAnts){
			int player = ant.resident().id();
			
			for (Tile x: rangeBorder(ant, position)){
				int enemyNr = enemyNr(x, player);
				
				(tmp[player]).put(x, enemyNr);
				if (player == 0 && enemyNr > 0)
					combat.add(x);
				attackable = rangeTiles(x, relativeAtackArea);
				for (Tile t: attackable){
					int val = Integer.MAX_VALUE;
					if (bestEnemy[player].containsKey(t) )
						val = bestEnemy[player].get(t);
					if (enemyNr < val)
						bestEnemy[player].put(t, enemyNr);
				}
				
			}
		}
		// verificam daca furnicile ataca, sunt atacate sau in zona de siguranta
		
		for (Tile ant: allAnts){
			int player = ant.resident().id();
			for (Tile x: rangeBorder(ant, position)){
				int enemyNr = 0;
				int minim = Integer.MAX_VALUE;
				//if (tmp[player].containsKey(x))
					enemyNr = tmp[player].get(x);
				
				for (int i = 0; i < MAXplayers; i++)
					if (i != player && bestEnemy[player].containsKey(x) &&
						bestEnemy[player].get(x) < minim)
						minim = bestEnemy[player].get(x);
				
				if (minim < enemyNr)
					result[player].put(x, OWNED); 	// die
				else if (minim == enemyNr)		
					result[player].put(x, ONE_ONE); 	// kill
				else result[player].put(x, SURVIVE); // safe
			}
		}
		
		// verific riscul unei furnici si decid daca o mut
		if (AGGRESSIVE && pozitive()){
			for (Tile t: enemies){
				HashSet<Tile> advance = rangeTiles(t, relativeAtackArea);
				int player = t.resident().id();
				
				for (Aim d: directions) {
					Tile x = antWorld.tile(t, d);
					int val = -1;
					if (result[player].containsKey(x))
						val = result[player].get(x);
					if (val >= ONE_ONE || !x.isPassable()){
						HashSet<Tile> visible = rangeTiles(x, relativeAtackArea);
						visible.removeAll(rangeTiles(t, relativeAtackArea));
						advance.addAll(visible);
					}
				}

			
				for (Tile x: advance) 
					if (result[0].containsKey(x) && result[0].get(x) <= ONE_ONE) {
						combat.removeAll(advance);
						break;
					}				
			} 
    	}
		
		// setez riscul in fiecare caz posibil
		for (Tile t: combat)
			if (result[0].get(t) == SURVIVE)	// daca furnica supravietuieste
				t.addscent(scent[SURVIVE]);
			else
				t.scent( scent[ result[0].get(t) ] ) ;	// daca este eliminata
	}
	
	private void orderMyAnts(){
		for (Tile t: food)
    		t.scent(-1.0);
		
		for (Tile t: myAnts){
			
			double score = t.scent();
			for (Aim d: directions){
				Tile x = antWorld.tile(t, d);
				score += x.scent();
			}
			t.weight(score);
			
		}
		
		List<Tile> tmp = new ArrayList<Tile>();
		for (Tile t: myAnts) tmp.add(t);
		Collections.sort(tmp);
		myAnts = new LinkedHashSet<Tile>();
		myAnts.addAll(tmp);
		//for (Tile t: myAnts){
		//	Logger.log(turn, t.scent() + "");
		//}
		//Logger.log(0,"");
	}
	
	private void gotoDestination() {
		HashSet<Tile> freeAnts = new HashSet<Tile>();		// lista de furnici disponibile pentru mutari
		HashSet<Tile> removed = new HashSet<Tile>();		// lista temporara de furnici care au primit comanda
    	HashSet<Tile> occupiedTile = new HashSet<Tile>();	// lista de celule in care exista deja furnici
    	HashMap<Tile, ArrayList<Aim>> willMove = new HashMap<Tile, ArrayList<Aim>>(); //
    	int unmoved = 0;
    	boolean foundMove = true;
    	
    	orderMyAnts();
    	//for (Tile t: myAnts)
    		
    	
    	freeAnts.addAll(myAnts);
    	   	
    	while (foundMove && timeLeft() > 5) {
    		foundMove = false;
	    	for (Tile ant: freeAnts) {
	    		Tile sol = null;
	    		Aim	order = null;		    		
	
	    		for (Aim d: directions) {
	    			Tile x = antWorld.tile(ant, d);
	    			
	    			if ( x.isEmpty() && !occupiedTile.contains(x)
	    			   && ( !willMove.containsKey(ant) || !willMove.get(ant).contains( d.behind()))
	    			   && (sol == null || compareScent(x, sol) > 0)) {
	    					sol = x;
	    					order = d;
	    					if( enemyHills.contains(x) ){
	    						enemyHills.remove(x);
	    					}
	    			}
	    		}
    	    	
	    		if (order == null || (willMove.containsKey(ant) && sol.scent() < 0)) {
	    			// Nu exista o mutare valida
	    			removed.add(ant);
	    			occupiedTile.add(ant);
	    			foundMove = true;
	    			unmoved++;
	    		} else {
	    			Tile dest = antWorld.tile(ant, order);
	    			if ( (willMove.containsKey(ant) && sol.scent() >= 0) || sol.scent() >  ant.scent()) {
	   
		    			if (freeAnts.contains(dest) && !removed.contains(dest)){
		    				ArrayList<Aim> list = willMove.get(dest);
		    				if (!willMove.containsKey(dest))
		    					willMove.put(dest, (list = new ArrayList<Aim>()));

		    				if (!list.contains(order)){
		    					list.add(order);
		    					if (list.size() > 1) Logger.log(2, "dim2 " + dest.toString());
		    					foundMove = true;
		    				}
		    			} else {	    			
			    			ant.resident().command(order);
			    			occupiedTile.add(dest);
			    			removed.add(ant);
			    			foundMove = true;
			    		}
	    			}
	    		}
    		}
	    	freeAnts.removeAll(removed);
	    	removed.clear();
    	}
    	unmoved += freeAnts.size();
    	
    	// in ultimele 150 de ture incerc sa nu am furnici nemiscate
    	if ((unmoved > 30 && turn < 850) || (unmoved > 15 && turn >=850)) AGGRESSIVE = true;
    }

	private int min (int x, int y){
		return (x < y) ? x: y;
	}
	
    public void explore() {
    	double FOOD = 8.0, ENEMY_HILL = 16.0, ENEMY_ANT = 1.0, MYHILL = 3.0, UNSEEN = 4.0, OLD = 1.0;
    	int ENEMIES = 4, DOMINATE = 2;
    	int VIEW, fight = timeLeft() / 2;
    	int MAX = 100000;
    	HashSet<Tile> old = new HashSet<Tile>();
    	
    	for (int i = 0; i < rows; i++)
    		for (Tile t : map[i])
        		if (t.isOld(turn))
            		old.add(t);
    	
    	extendArea (enemyHills, ENEMY_HILL, MAX);	
    	
    	for (Tile f: food) {
    		HashSet<Tile> position = new HashSet<Tile>( Arrays.asList(f));
    		Area area = extendArea(position, FOOD, 1);
    		if (area.nearEnemy - area.nearAnt < 0 && area.nearEnemy > 0)
    			extendArea(position, -FOOD, 1);
    	}	
      	
    	// pentru celulele periferice (aflate la marginea zonei vizibile) se extinde scent-u pe cat posibil
    	extendArea(periferic, UNSEEN, MAX);
    	
    	// pentru celulele vizitate cu un timp in urma se extinde scent-ul daca numarul acstora este destul de mare
    	VIEW = min(stats[turn], (rows * cols) / antWorld.viewradius2()) / 2;
    	if (old.size() < antWorld.turns() / 100 + 20)
    		for (Tile t: old) {
    			// ne oprim la prima furnica din raza extinsa
    			extendArea(new HashSet<Tile>( Arrays.asList(t)), OLD, 1);
		    	if (timeLeft() < fight) break;
			}   		
    	else
    		extendArea( old, OLD, VIEW);
    	
    	for (Tile t: hills) {    		
    		int defend = stats[turn] / (3 * hills.size());
    		if (defend > 0) {
    			HashSet<Tile> base = rangeTiles(t, relativeHillArea);
	    		Area r = extendArea(base, 0, min(ENEMIES, defend));
	    		int ATTACK = min(r.enemyAnts + DOMINATE, defend);
	    		if ((r.nearEnemy > 0 && r.nearEnemy - r.nearAnt < ENEMIES) || r.dangerZone > 0) {
					if (r.nearEnemy > ENEMIES && r.dangerZone > ENEMIES)   			   		
						extendArea(base, MYHILL, ATTACK);
					else
						extendArea(	new HashSet<Tile>( Arrays.asList(t)), MYHILL, ATTACK );
				}
    		}
    		if (turn % (3) != 0) t.addscent(-OLD);
    	}
    	
    	for (Tile t: enemies) {
    		HashSet<Tile> visible = rangeTiles(t, relativeAtackArea);
    		Area area = extendArea(visible, 0, ENEMIES);
    		if (area.safeZone > 0)
    			extendArea(visible, ENEMY_ANT, area.ants + DOMINATE);
    		t.scent(-OLD);
    	}
    	
		gotoDestination();

    	//calculateRisk(); 

    }
}
