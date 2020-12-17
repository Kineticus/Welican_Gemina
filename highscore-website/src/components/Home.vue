<template>
   <div>
     <HighscoreTable game="fallios"></HighscoreTable>
     <HighscoreTable game="block-breaker"></HighscoreTable>
     <HighscoreTable game="daddy-worm-1p"></HighscoreTable>
     <HighscoreTable game="daddy-worm-2p"></HighscoreTable>
   </div>
</template>

<script>
import UsersDataService from "../services/usersDataService";
import HighscoreTable from './HighscoreTable.vue';

export default {
  name: "home",
  components: {
    HighscoreTable
  },
  data() {
    return {
      highscores: []
    };
  },
  methods: {
    onDataChange(items) {
      let _highScores = [];
      items.forEach((item) => {
        var hs = item.val();
        _highScores.push({
          id: item.key,
          highscore: hs,
        });
      });
      this.highscores = _highScores;
    }
  },
  mounted() {
    UsersDataService.getHighscores().then((snapshot) => {
        console.log("/Highscores", snapshot.val());
        this.onDataChange(snapshot);
    });
  },
  beforeUnmount() { 
  }
}
</script>

<style>

</style>