using System;
using System.Collections.Generic;
using System.Linq;

class Program {
    static List<string> Split(string s) {
        return s.Split(' ', StringSplitOptions.RemoveEmptyEntries).ToList();
    }

    static void Main() {
        int n = int.Parse(Console.ReadLine());
        Dictionary<string, HashSet<string>> adj = new Dictionary<string, HashSet<string>>();

        for (int i = 0; i < n; i++) {
            string s = Console.ReadLine();
            List<string> v = Split(s);
            
            for (int j = 1; j < v.Count; j++) {
                if (!adj.ContainsKey(v[0]))
                    adj[v[0]] = new HashSet<string>();
                if (!adj.ContainsKey(v[j]))
                    adj[v[j]] = new HashSet<string>();
                    
                adj[v[0]].Add(v[j]);
                adj[v[j]].Add(v[0]);
            }
        }

        string[] endpoints = Console.ReadLine().Split();
        string start = endpoints[0];
        string end = endpoints[1];

        Dictionary<string, string> prev = new Dictionary<string, string>();
        prev[start] = "thisisthestart";

        Queue<string> q = new Queue<string>();
        q.Enqueue(start);
        
        while (q.Count > 0) {
            string curr = q.Dequeue();

            if (adj.ContainsKey(curr)) {
                foreach (string next in adj[curr]) {
                    if (!prev.ContainsKey(next)) {
                        prev[next] = curr;
                        q.Enqueue(next);
                    }
                }
            }
        }

        if (!prev.ContainsKey(end)) {
            Console.WriteLine("no route found");
            return;
        }

        List<string> ans = new List<string>();
        string current = end;
        while (current != "thisisthestart") {
            ans.Add(current);
            current = prev[current];
        }
        ans.Reverse();

        Console.WriteLine(string.Join(" ", ans));
    }
}