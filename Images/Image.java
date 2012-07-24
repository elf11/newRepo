import java.util.*;
import java.io.*;

/*
 *  medie foreground = medie_fg
 *  medie background = medie_fg 
 *  
 *  standard deviation background = deviation_bg
 *  standard deviation foreground = deviation_fg
 * 
 */


/*
 * Clasa Node retine structura unui nod, id - ul, nr de arce si costul fiecarui arc
 */
class Node {
	int id;
	int n;
	int[] edges = new int[n];
	double[] cost  = new double[n];
	
	public Node(){}
	
}

/*
 * Clasa Cost se calculeaza cele doua costuri -foreground si background cu ajutorul formulelor
 */

class Cost{
	
	public Cost(){
		
	}
	
	double costF(int pixel, double medie_fg, double deviation_fg){
		
		double cost = 0;
		
		cost = Math.pow((pixel - medie_fg) / deviation_fg, 2);
		cost = 0.5 * cost + Math.log(Math.sqrt(2 * Math.PI * Math.pow(deviation_fg, 2)));
		
		if(cost > 10){
			return 10;
		}else{
			return cost;
		}
	
	}
	
	double costG(int pixel, double medie_bg, double deviation_bg){
		
		double cost;
		
		cost = Math.pow((pixel - medie_bg) / deviation_bg, 2);
		cost = 0.5 * cost  + Math.log(Math.sqrt(2 * Math.PI * Math.pow(deviation_bg, 2)));
		
		if(cost > 10){
			return 10;
		}else{
			return cost;
		}
		
	}
	
}

/*
 * BFS - se realizeaza o parcurgere BFS a grafului
 * 
 */

class BFS{
	
	public BFS(){}
	
	double calculateBFS(List<Node> graph, int src, int dest, int[] parents){
		
		int u ,v;
		int nr = graph.size();
		double cost;
		double[] matrix = new double[nr];
		
		Queue<Integer> q = new LinkedList<Integer>();
		
		parents[src] = -2;
		
		matrix[src] = Integer.MAX_VALUE;
		
		q.add(src);
		while(!q.isEmpty()){
			
			u = q.poll();
			for(int i = 0; i < graph.get(u).n; i++){
				v = graph.get(u).edges[i];
				cost = graph.get(u).cost[i];
				
				if(cost > 0 && parents[v] == -1){
					parents[v] = u;
					
					if(matrix[u] < cost){
						matrix[v] = matrix[u];
					}else{
						matrix[v] = cost;
					}
					
					if(v != dest){
						q.add(v);
					}else{
						return matrix[v];
					}
				}
				
			}
			
			
		}
		
		return 0;
		
	}
	
}

/*
 * Clasa Average - aici se calculeaza atat mediile pentru foreground si background cat si deviatiile standard
 * 
 */

class Average{
	
	public Average(){}
	
	double averageBG(int[][] img, int rows, int cols, int[][] img_bg){
		
		int sum = 0;
		int pixels_bg = 0;
		
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				if(img_bg[i][j] != 0){
					sum = sum + img[i][j];
					pixels_bg++;
				}
			}
		}
		return ((double)sum) / pixels_bg;
		
	}
	
	double averageFG(int[][] img, int rows, int cols, int[][] img_fg){
		
		int sum = 0;
		int pixels_fg = 0;
		
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				if(img_fg[i][j] != 0){
					sum = sum + img[i][j];
					pixels_fg++;
				}
			}
		}
		return ((double)sum) / pixels_fg;
		
	}
	
	double deviationBG(double medie_bg, int[][] img, int[][] img_bg, int rows, int cols){
		
		double deviation = 0;
		int pixels_bg = 0;
		
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				if(img_bg[i][j] != 0){
					deviation = deviation + Math.pow(medie_bg - img[i][j], 2);
					pixels_bg++;
				}
			}
		}
		
		return Math.sqrt(deviation / pixels_bg);
	}
	
	double deviationFG(double medie_fg, int[][] img, int[][] img_fg, int rows, int cols){
		
		double deviation = 0;
		int pixels_fg = 0;
		
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				if(img_fg[i][j] != 0){
					deviation = deviation + Math.pow(medie_fg - img[i][j], 2);
					pixels_fg++;
				}
			}
		}
		
		return Math.sqrt(deviation / pixels_fg);
	}
	
}


public class Image {
	
	public static void main(String[] args) throws IOException{
		
		long time = System.currentTimeMillis();
		
		FileInputStream fstream  = new FileInputStream("imagine.pgm");
		DataInputStream in_img = new DataInputStream(fstream);
		BufferedReader br_img = new BufferedReader(new InputStreamReader(in_img)); 
		
		FileInputStream file  = new FileInputStream("mask_bg.pgm");
		DataInputStream in_bg = new DataInputStream(file);
		BufferedReader br_bg = new BufferedReader(new InputStreamReader(in_bg)); 
		
		FileInputStream f  = new FileInputStream("mask_fg.pgm");
		DataInputStream in_fg = new DataInputStream(f);
		BufferedReader br_fg = new BufferedReader(new InputStreamReader(in_fg));
		
		FileInputStream f1  = new FileInputStream("parametri.txt");
		DataInputStream in_par = new DataInputStream(f1);
		BufferedReader br_par = new BufferedReader(new InputStreamReader(in_par)); 
		
		
		int rows, cols, max, lambda = 0, treshold = 0;
		String header;
		String strLine;
		double medie_fg = 0;
		double medie_bg = 0;
		double deviation_fg = 0;
		double deviation_bg = 0;
		
		header = br_img.readLine();
		strLine = br_img.readLine();
		String[] tokens = strLine.split(" ");
		rows = Integer.parseInt(tokens[1]);
		cols = Integer.parseInt(tokens[0]);
		strLine = br_img.readLine();
		max = Integer.parseInt(strLine);
		for(int i = 0; i < 3; i++){
			strLine = br_bg.readLine();
		}
		
		for(int i = 0; i < 3; i++){
			strLine = br_fg.readLine();
		}
		
	
		int[][] img = new int[rows][cols];
		int[][] img_bg = new int[rows][cols];
		int[][] img_fg = new int[rows][cols];
		
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				strLine = br_img.readLine();
				img[i][j] = Integer.parseInt(strLine);
			}
		}
		
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				strLine = br_bg.readLine();
				img_bg[i][j] = Integer.parseInt(strLine);
			}
		}
		
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				strLine = br_fg.readLine();
				img_fg[i][j] = Integer.parseInt(strLine);
			}
		}
		int k = 0;
		while((strLine =  br_par.readLine()) != null){
			
			//valabila atunci cand parametrii sunt dati pe o singura linie
			
			/*
			String[] tokenss;
			tokenss = strLine.split(" ");
			lambda = Integer.parseInt(tokenss[0]);dtrL
			treshold = Integer.parseInt(tokens[1]);
			*/
			
			
			//valabila atunci cad parametrii sunt dati pe linii diferite
			if(k == 0){
				lambda = Integer.parseInt(strLine);
			}
			if(k == 1){
				treshold = Integer.parseInt(strLine);
			}
			k++;
			
		}
		
		
		
		Average avg = new Average();
		
		medie_fg = avg.averageFG(img, rows, cols, img_fg);
		medie_bg = avg.averageBG(img, rows, cols, img_bg);
		
		deviation_fg = avg.deviationFG(medie_fg, img, img_fg, rows, cols);
		deviation_bg = avg.deviationFG(medie_bg, img, img_bg, rows, cols);
		
		
		List<Node> graph = new ArrayList<Node>();
		
		
		Node aux =  new Node();
		Node nf = new Node();
		Node ng = new Node();
		
		int nr_e;
		int[] edges = new int[6];
		
		double cst;
		double[] cost = new double[6];
		
		nf.id = rows * cols;
		ng.id = nf.id + 1;
		nf.n = 0;
		ng.n = 0;
		nf.edges = new int[rows*cols];
		nf.cost = new double[rows*cols];
		ng.edges = new int[rows*cols];
		ng.cost = new double[rows*cols];
		
		int[] vi = new int[4];
		vi[0] = -1;
		vi[1] = 0;
		vi[2] = 0;
		vi[3] = 1;
		
		int[] vj = new int[4];
		vj[0] = 0;
		vj[1] = -1;
		vj[2] = 1;
		vj[3] = 0;
		int i1, j1;
		
		/*
		FileOutputStream out = new FileOutputStream("my-graf.txt");
		PrintStream pout = new PrintStream(out);
		*/
		
		Cost ct = new Cost();
		
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				aux = new Node();
				aux.id = i * cols + j;
				nr_e = 0;
				
				
				cst = ct.costF(img[i][j], medie_fg, deviation_fg);
				edges[nr_e] = nf.id;
				cost[nr_e] = cst;
				nr_e++;
				nf.edges[nf.n] = aux.id;
				nf.cost[nf.n] = cst;
				nf.n++;
				
				cst = ct.costG(img[i][j], medie_bg, deviation_bg);
				edges[nr_e] = ng.id;
				cost[nr_e] = cst;
				nr_e++;
				ng.edges[ng.n] = aux.id;
				ng.cost[ng.n] = cst;
				ng.n++;
				
				
				for(int l = 0; l < 4; l++){
					i1 = i + vi[l];
					j1 = j + vj[l];
					if(i1 >= 0 && i1 < rows && j1 >= 0 && j1 < cols){
						if(Math.abs(img[i][j] - img[i1][j1]) <= treshold){
							edges[nr_e] = i1 * cols + j1;
							cost[nr_e] = lambda;
							nr_e++;
						}
					}
				}
				
				
				aux.n = nr_e;
				aux.edges = new int[nr_e];
				for(int m = 0; m < nr_e; m++){
					aux.edges[m] = edges[m];
				}
				aux.cost = new double[nr_e];
				for(int m = 0; m < nr_e; m++){
					aux.cost[m] = cost[m];
				}
				
				/*
				pout.println("\r\n nod:" + (aux.id + 1) + " "+ img[i][j] + "\r\n");
				
				for(int m = 0; m < aux.n; m++){
					pout.println("v:" + (aux.edges[m] + 1) + ", c:" + cost[m] + ", f:0.0");
					
				}*/
				
				graph.add(aux);
				
				
			}
		}
		
		graph.add(nf);
		graph.add(ng);
		
		BFS bfs = new BFS();
		double flux_max = 0;
		
		int[] parents = new int[graph.size()];
		
		/*
		 * Calculam fluxul cu ajutorul algoritmului Edmonds-Karp
		 */
	
		while(true){
			
			for(int j = 0; j < parents.length; j++){
				parents[j] = -1;
			}
			
			double flux;
			flux = bfs.calculateBFS(graph, nf.id, ng.id, parents);
			
			flux_max = flux_max + flux;
			
			
			if(flux == 0.0){
				break;
			}
			
			int auxiliar = ng.id;
			
			while(auxiliar != nf.id){
				
				for(int m = 0; m < graph.get(parents[auxiliar]).n; m++){
					if(graph.get(parents[auxiliar]).edges[m] == auxiliar){
						
						graph.get(parents[auxiliar]).cost[m] = graph.get(parents[auxiliar]).cost[m] - flux;
						break;
						
					}
				}
				
				auxiliar = parents[auxiliar];
			}
			
		}
		
		int[] result = new int[graph.size()];
		
		for(int m = 0; m < graph.size(); m++){
			result[m] = 255;
		}
		
		Queue<Integer> q = new LinkedList<Integer>();
		int v, u;
		q.add(nf.id);
		
		while(!q.isEmpty()){
			u = q.poll();
			
			
			for(int n = 0; n < graph.get(u).n; n++){
				v = graph.get(u).edges[n];
				
				if(result[v] == 255 && graph.get(u).cost[n] > 0){
					result[v] = 0;
					q.add(v);
				}
			}
		}
		
		System.out.println("Fluxul maxim este: " + flux_max);
		
		//deschidem fisierul pentru a scrie in el imaginea rezultata
		
		FileOutputStream fo = new FileOutputStream("segment.pgm");
		PrintStream ps = new PrintStream(fo);
		
		
		ps.println(header);
		ps.println(cols + " " + rows);
		ps.println(max);
		
		
		for(int m = 0; m < graph.size() - 2; m++){
			ps.println(result[m]+ " ");
		}
		
		ps.close();
		
		//System.gc();
		
		Runtime runtime = Runtime.getRuntime();
		
		runtime.gc();
		long memory = runtime.totalMemory() - runtime.freeMemory();
		System.out.println("Used memory is megabytes: " + ((double) memory)/(1024*1024));
		
		System.out.println(System.currentTimeMillis() - time);
	}

}