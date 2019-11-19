import collections

class Solution(object):
    def removeStones(self, stones):
        """
        :type stones: List[List[int]]
        :rtype: int
        """
        rows = collections.defaultdict(set)
        cols = collections.defaultdict(set)
        for i, j in stones:
            rows[i].add(j)
            cols[j].add(i)

        def dfsRow(i):
            seenR.add(i)
            for j in rows[i]:
                if j not in seenC:
                    dfsCol(j)

        def dfsCol(j):
            seenC.add(j)
            for i in cols[j]:
                if i not in seenR:
                    dfsRow(i)

        def dfs(row, col):
            seenR.add(row)
            seenC.add(col)
            for next_col in rows[row]:
                if next_col not in seenC:
                    dfs(row, next_col)
            for next_row in cols[col]:
                if next_row not in seenR:
                    dfs(next_row, col)

        seenR, seenC = set(), set()
        islands = 0
        for i, j in stones:
            if i not in seenR:
                islands += 1
                dfs(i, j)
                
        return len(stones) - islands


stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]

solution = Solution()

print(solution.removeStones(stones))