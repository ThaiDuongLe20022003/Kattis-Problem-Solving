using System;
using System.Collections.Generic;

public class Point : IEquatable<Point>
{
    public int X { get; set; }
    public int Y { get; set; }
    
    public Point(int x, int y)
    {
        X = x;
        Y = y;
    }
    
    public override bool Equals(object obj)
    {
        return Equals(obj as Point);
    }
    
    public bool Equals(Point other)
    {
        return other != null && X == other.X && Y == other.Y;
    }
    
    public override int GetHashCode()
    {
        return (X * 397) ^ Y;
    }
}

public class Program
{
    public static void Main()
    {
        int n = int.Parse(Console.ReadLine());
        Console.ReadLine(); // Consume blank line
        
        for (int pathNum = 0; pathNum < n; pathNum++)
        {
            int s = int.Parse(Console.ReadLine());
            
            Dictionary<Point, HashSet<Point>> adj = new Dictionary<Point, HashSet<Point>>();
            Point currentPos = new Point(0, 0);
            Point startNode = new Point(0, 0);
            
            for (int i = 0; i < s; i++)
            {
                char dirChar = Console.ReadLine()[0];
                
                Point nextPos = new Point(currentPos.X, currentPos.Y);
                switch (dirChar)
                {
                    case 'N': nextPos.Y++; break;
                    case 'E': nextPos.X++; break;
                    case 'S': nextPos.Y--; break;
                    case 'W': nextPos.X--; break;
                }
                
                // Add bidirectional edges
                if (!adj.ContainsKey(currentPos))
                    adj[currentPos] = new HashSet<Point>();
                if (!adj.ContainsKey(nextPos))
                    adj[nextPos] = new HashSet<Point>();
                    
                adj[currentPos].Add(nextPos);
                adj[nextPos].Add(currentPos);
                
                currentPos = nextPos;
            }
            Point foodLocation = currentPos;
            
            // BFS
            Dictionary<Point, int> dist = new Dictionary<Point, int>();
            Queue<Point> queue = new Queue<Point>();
            int shortestPath = -1;
            
            dist[startNode] = 0;
            queue.Enqueue(startNode);
            
            while (queue.Count > 0)
            {
                Point u = queue.Dequeue();
                int d = dist[u];
                
                if (u.Equals(foodLocation))
                {
                    shortestPath = d;
                    break;
                }
                
                if (adj.ContainsKey(u))
                {
                    foreach (Point v in adj[u])
                    {
                        if (!dist.ContainsKey(v))
                        {
                            dist[v] = d + 1;
                            queue.Enqueue(v);
                        }
                    }
                }
            }
            
            Console.WriteLine(shortestPath);
            
            // Consume blank line if not last path
            if (pathNum < n - 1)
                Console.ReadLine();
        }
    }
}