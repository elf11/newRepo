import java.io.FileOutputStream;
import java.io.PrintStream;
import java.io.PrintWriter;

public class MyBot implements Bot {
	
	public static PrintWriter file = null;
	static Strategy strategy = Strategy.getInstance();
	
	public MyBot() {
		try{
			file = new PrintWriter("log.txt");
			file.println("constr strategy");
			file.flush();
		} catch(Exception e) {}
		
	}
	
	public static void main(String[] args) {
		try{
			System.setErr(new PrintStream(new FileOutputStream("eroare.txt")));
		} catch(Exception e) {}
		Ants.run(new MyBot(), strategy);
	}
	
	public void do_turn(Ants ants) {
		//strategy.seeIfNewAnt();
		strategy.setTurnStartTime(System.currentTimeMillis());
		strategy.turnInit();
		strategy.resetMap();
		strategy.markVisible();
		strategy.explore();
		
	}
}

