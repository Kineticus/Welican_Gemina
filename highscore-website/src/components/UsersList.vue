<template>
  <vuetable ref="vuetable"
    :fields="['id', 'name', 'wifiName', 'zipcode', 'timezone']"
    :api-mode="false"
    :data="users"
  ></vuetable>
</template>

<script>
import Vuetable from 'vuetable-2'
import UsersDataService from "../services/UsersDataService";
export default {
  name: "users-list",
  components: {
    Vuetable
  },
  data() {
    return {
      users: [],
    };
  },
  methods: {
    onDataChange(items) {
      let _users = [];
      items.forEach((item) => {
        var user = item.val();
        _users.push({
          id: item.key,
          name: user.name,
          wifiName: user.wifiName,
          createdDate: user.createdDate,
          timezone: user.timezone,
          zipcode: user.zipcode,
        });
      });
      this.users = _users;
    },
  },
  mounted() {
    var items;
    UsersDataService.getAll().then((snapshot) => {
        console.log("/Users", snapshot.val());
        this.users.push(snapshot.val());
        this.onDataChange(snapshot);
    });
  },
  beforeDestroy() {
  }
};
</script>

<style>
.list {
  text-align: left;
  max-width: 750px;
  margin: auto;
}
</style>