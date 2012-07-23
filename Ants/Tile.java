/**
 * aceasta clasa retine informatiile legate de celula de pa harta la pozitia (row, col)
 * @author bogdan
 *
 */
public class Tile implements Comparable<Tile>{
	private int row;
	private int col;
	private Ilk content; 	// ce se afla in celula de pe harta
	private int lastEmpty; 	// turul la care a fost vizitata celula ultima data
	private int lastVisible;
	private Ant resident; 	// referinta catre o instata de furnica daca aceasta se afla in celula
	private double scent;
	private double weight;
	private double seed;
	
	Tile(int r, int c) {
		row = r;
		col = c;
		content = Ilk.UNSEEN;
		lastEmpty = 0;
		lastVisible = 0;
	}
	
	public int row() { return row; }
	public int col() { return col; }
	
	public void content( Ilk i ) { content = i; }
	public Ilk  content() { return content; }
	
	public void lastEmpty(int t) { lastEmpty = t; }
	public int  lastEmpty() { return lastEmpty; }
	
	public void resident(Ant a) { resident = a; }
	public Ant resident() { return resident; }
	
	
	public void lastVisible(int v) { lastVisible = v; }
	public int lastVisible() { return lastVisible; }
	
	public void scent(double s) { 
	//	if (s != 0.0) Logger.log(Strategy.getAnts().turn(), "set " + s);
		scent = s; }
	public double scent() {
	//	if (scent != 0.0) Logger.log(Strategy.getAnts().turn(), "get " + scent);
		return scent; }
	public void addscent (double s) { 
	//	if (s != 0.0) Logger.log(Strategy.getAnts().turn(), "add " + s);
		scent += s; }
	
	public void weight(double s) { weight = s; }
	public double weight() { return weight; }
	
	public void seed(double s) { seed = s; }
	public double seed() { return seed; }
	
	public boolean isPassable(){
		if (lastVisible > 0 && content != Ilk.WATER) return true;
		return false;
	}
	
	public int hashCode() {
		return this.row * 1000 + this.col;
	}
	
	public boolean equals(Object o) {
			return row == ((Tile) o).row() && col == ((Tile) o).col();
	}

	public boolean isEmpty() {
		if (resident == null && content != Ilk.WATER && content != Ilk.FOOD) return true;
		return false;
	}
	
	public boolean isOld(int turn) {
		return (isPassable() && lastVisible > 0 && turn - lastVisible > 3);
	}
	
	public int compareTo(Tile t){
		if (weight < t.weight()) return -1;
		else if (weight > t.weight) return 1;
		 	else 
				 return (seed < t.seed()) ? -1 : 1;	
	}
	
	public String toString() {
		return "(" + this.row + "," + this.col + ")";
	}
}