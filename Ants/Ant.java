
/**
 * Clasa Ant retine informatii necesare unei furnici pentru a efectua o mutare
 * @author bogdan
 */

public class Ant {
	private final int id; // id-ul furnicii
	private Tile pos;

	public Ant(int idD, Tile p) {
		id = idD;
		pos = p;
	}
	
	public int id() { return id; } 
	
	public void command(Aim command) {
		if ( command == null ) return;
		Strategy.getAnts().issueOrder(pos, command);
	}
}
