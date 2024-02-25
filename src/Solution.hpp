#pragma once

#include <string>
#include <algorithm>
#include <map>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <unordered_set>
#include <numeric>

namespace my {
class Solution {
    static constexpr int NoMeeting = -1;

    int n;
    std::unordered_set<int> whoKnows;
    std::vector<std::unordered_set<int>> pendingMettings;
    std::vector<int> personInMettingId;

    void setFirstPersionWhichKnows(int firstPerson)
    {
        whoKnows = {};
        whoKnows.insert(0);
        whoKnows.insert(firstPerson);
        personInMettingId.resize(n);
        resetMeeting();
    }

    void resetMeeting()
    {
        pendingMettings.clear();
        std::ranges::fill(personInMettingId, NoMeeting);
    }

    void commitMettings()
    {
        for (const auto& metting : pendingMettings) {
            if (someoneInMeetingKnows(metting)) {
                addToWhoKnows(metting);
            }
        }
        resetMeeting();
    }

    bool someoneInMeetingKnows(const std::unordered_set<int>& whoIsPressent) const
    {
        for (auto person : whoIsPressent) {
            if (whoKnows.contains(person)) {
                return true;
            }
        }
        return false;
    }

    void addToWhoKnows(const std::unordered_set<int>& whoIsPressent)
    {
        whoKnows.insert(whoIsPressent.begin(), whoIsPressent.end());
    }

    void addMetting(int a, int b)
    {
        auto aInMeeting = personInMettingId[a];
        auto bInMeeting = personInMettingId[b];
        if (aInMeeting == NoMeeting && bInMeeting == NoMeeting) {
            int newMettingId = static_cast<int>(pendingMettings.size());
            pendingMettings.emplace_back();
            addPersonToMeeting(a, newMettingId);
            addPersonToMeeting(b, newMettingId);
        } else if (aInMeeting == NoMeeting) {
            addPersonToMeeting(a, bInMeeting);
        } else if (bInMeeting == NoMeeting) {
            addPersonToMeeting(b, aInMeeting);
        } else if (aInMeeting != bInMeeting) {
            joinMeetings(aInMeeting, bInMeeting);
        }
    }

    void addPersonToMeeting(int person, int meeting)
    {
        personInMettingId[person] = meeting;
        pendingMettings[meeting].insert(person);
    }

    void joinMeetings(int a, int b)
    {
        for (auto person : pendingMettings[b]) {
            personInMettingId[person] = a;
        }
        pendingMettings[a].merge(std::move(pendingMettings[b]));
        pendingMettings[b] = {};
    }

    std::vector<int> makeSecretReport()
    {
        return {whoKnows.begin(), whoKnows.end()};
    }

public:
    std::vector<int> findAllPeople(int n, std::vector<std::vector<int>>& meetings, int firstPerson)
    {
        std::sort(meetings.begin(), meetings.end(), [](const auto& a, const auto& b) { return a[2] < b[2]; });
        this->n = n;
        setFirstPersionWhichKnows(firstPerson);

        int lastMeetingTime = 0;
        for (auto& meeting : meetings) {
            auto time = meeting[2];
            if (time != lastMeetingTime) {
                commitMettings();
            }
            lastMeetingTime = time;
            addMetting(meeting[0], meeting[1]);
        }
        commitMettings();

        return makeSecretReport();
    }
};
}

namespace my2 {

class Groups {
public:
    explicit Groups(int itemCount) : mGroups(itemCount) {
        int i = 0;
        for (auto& item : mGroups) {
            item = GropItem(i++);
        }
    }
    
    void join(int a, int b)
    {
        auto groupA = mGroups.at(a);
        auto groupB = mGroups.at(b);
        if (groupA.root != groupB.root) {
            if (groupA.root > groupB.root) {
                std::swap(a, b);
                std::swap(groupA, groupB);
            }
            mGroups[findLastIn(a)].next = groupB.root;
            assingNewRoot(groupB.root, groupA.root);
        }
    }
    
    void clearNoneZeroGroups()
    {
        auto id = 0;
        for(auto& item : mGroups)
        {
            if (item.root)
            {
                item = GropItem{id};
            }
            ++id;
        }
    }
    
    std::vector<int> groupIndexes(int i) const noexcept
    {
        std::vector<int> result;
        result.reserve(mGroups.size());
        
        result.push_back(i);
        while (mGroups.at(i).next != i) {
            i = mGroups.at(i).next;
            result.push_back(i);
        }
        return result;
    }
    
private:
    int findLastIn(int i) {
        while (mGroups.at(i).next != i) {
            i = mGroups.at(i).next;
        }
        return i;
    }
    
    void assingNewRoot(int from, int to)
    {
        mGroups.at(from).root = to;
        while (mGroups.at(from).next != from) {
            mGroups.at(from).root = to;
            from = mGroups.at(from).next;
        }
    }
    
private:
    struct GropItem {
        int root;
        int next;
        
        GropItem() {}
        explicit GropItem(int x) : root{x}, next{x}
        {}
    };
    
    std::vector<GropItem> mGroups;
};

class Solution {
public:
    std::vector<int> findAllPeople(int n, std::vector<std::vector<int>>& meetings, int firstPerson)
    {
        std::sort(meetings.begin(), meetings.end(), [](const auto& a, const auto& b) { return a[2] < b[2]; });
        
        Groups groups{n};
        groups.join(0, firstPerson);
        
        int lastMeetingTime = 0;
        for (auto& meeting : meetings) {
            auto time = meeting[2];
            if (time != lastMeetingTime) {
                groups.clearNoneZeroGroups();
            }
            lastMeetingTime = time;
            groups.join(meeting[0], meeting[1]);
        }

        return groups.groupIndexes(0);
    }
};
}

namespace leetcode {
using namespace std;

class UnionFindSet {
    public:
        UnionFindSet(int n) : _parent(n), _size(n) {
            for (int i=0; i<n; i++) {
                _parent[i] = i;
                _size[i] = 1;
            }
        }
        bool Union(int x, int y) {
            int rootX = Find(x);
            int rootY = Find(y);

            if(rootX==rootY)
                return true;

            if(rootX != rootY){
                if(_size[rootY]<_size[rootX]){
                    _parent[rootY] = rootX;
                    _size[rootX]+=_size[rootY];
                }
                else{
                    _parent[rootX] = rootY;
                    _size[rootY]+=_size[rootX];

                }
            }
            return false;
        }
        int Find(int x) {
            if (_parent[x] == x) {
                return x;
            }
            return _parent[x] = Find(_parent[x]);
        }
        int getGroup(){
            int g = 0;
            for(int i = 0; i <_parent.size(); i++){
                if(i==_parent[i])
                    g++;
            }
            return g;
        }
        vector<int> getGroupVec(){
            vector<int> res;
            for(int i = 0; i <_parent.size(); i++){
                if(_parent[0]==_parent[i])
                    res.push_back(i);
            }
            return res;
        }
        void set(int num){
            //cout << num << endl;
            _parent[num] = num;
            _size[num] = 1;
        }
    private:
        vector<int> _parent;
        vector<int> _size;
};

class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        sort(meetings.begin(), meetings.end(), [&](vector<int>& a, vector<int>& b){
            return a[2]<b[2];
        });
        //for(auto& meet : meetings){
        //    cout << meet[0] << " " << meet[1] << " " << meet[2] << endl;
        //}
        vector<int> res(1, 0);
        UnionFindSet ufs(n);
        ufs.Union(0, firstPerson);
        int m = meetings.size();
        for(int i = 0; i < m; i++){
            int time = meetings[i][2];
            ufs.Union(meetings[i][0], meetings[i][1]);
            if(i==m-1 || meetings[i][2]!=meetings[i+1][2]){
                int j = i;
                while(j>=0 && meetings[j][2]==time){
                    if(ufs.Find(meetings[j][1])!=ufs.Find(0))
                        ufs.set(meetings[j][1]);
                    if(ufs.Find(meetings[j][0])!=ufs.Find(0))
                        ufs.set(meetings[j][0]);
                    j--;
                }
            }
        }
        //cout << "------------" << endl;
        return ufs.getGroupVec();
    }
};
}
