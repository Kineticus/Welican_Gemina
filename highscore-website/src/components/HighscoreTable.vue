<template>
   <div>
      <h2>{{this.game}} HIGHSCORES</h2>
<table class="table is-bordered is-striped is-narrow is-hoverable is-fullwidth">
    <thead>
      <tr>
        <th><abbr title="Id">Id</abbr></th>
        <th><abbr title="name">Highscore</abbr></th>
      </tr>
    </thead>
    <tbody>
        <tr v-for="hs in highscores" :key="hs.id">
          <td>{{hs.id}}</td>
          <td>{{hs.highscore}}</td>
        </tr>
    </tbody>
  </table>
   </div>
</template>

<script>
import UsersDataService from "../services/usersDataService";

export default {
  name: "highscore-table",
  components: {
  },
  data() {
    return {
      game: this.$attrs.game,
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
    UsersDataService.getSpecificHighscores(this.game).then((snapshot) => {
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